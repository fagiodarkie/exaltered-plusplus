#include "screen/qexperience_screen.h"
#include "layout/qborderlayout.h"

#include <QTabWidget>
#include <QFormLayout>
#include <QLabel>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QScrollArea>
#include "widget/std_compatible.h"

namespace qt { namespace screen {

    qexperience_screen::qexperience_screen(std::shared_ptr<character::character> character,
                                           manager::character_manager &ch_manager,
                                           QWidget *parent) : QWidget(parent), _character(character), _character_manager(ch_manager)
    {
      open_logger = new QPushButton("Add session");

      _logger = new widget::session_experience_logger;

      connect(open_logger, &QPushButton::clicked, _logger, &QDialog::show);
      connect(_logger, &widget::session_experience_logger::session_logged, this, &qexperience_screen::add_session);

      layout::QBorderLayout *outer = new layout::QBorderLayout;

      awards = new QWidget;
      expenses = new QWidget;

      refresh();

      QTabWidget *center = new QTabWidget;
      center->setTabPosition(QTabWidget::TabPosition::North);
      center->addTab(expenses, "Experience Purchases");
      center->addTab(awards, "Experience Awards");
      outer->addWidget(center, layout::QBorderLayout::Center);

      recompute_logger_session();
      setLayout(outer);
    }

    void qexperience_screen::recompute_logger_session()
    {
      _logger->set_next_session_number(_character->get_experience().last_session() + 1);
    }

    void qexperience_screen::add_session(std::vector<character::narrative::experience_award> awards)
    {
      for (auto award: awards)
        _character->get_experience().award(award);

      _character_manager.save_character(_character);

      _logger->set_next_session_number(_character->get_experience().last_session() + 1);
      _logger->hide();

      refresh_awards();
    }

    void qexperience_screen::refresh() const
    {
        refresh_awards();
        refresh_expenses();
    }

    void qexperience_screen::refresh_awards() const
    {
      qDeleteAll(awards->children());
      delete awards->layout();
      QVBoxLayout *list = new QVBoxLayout;
      QWidget *listwidget = new QWidget;
      layout::QBorderLayout* outer = new layout::QBorderLayout;

      for (unsigned int i = 0; i <= _character->get_experience().last_session(); ++i)
        {
          auto entries = _character->get_experience().awards_on_session(i);
          if (entries.empty())
            continue;

          QGroupBox *session_group = new QGroupBox(QString("Session #%1").arg(i));
          QVBoxLayout *inner = new QVBoxLayout;
          for (auto entry: entries)
            inner->addWidget(label(entry.summary()));

          session_group->setLayout(inner);
          list->addWidget(session_group);
        }

      listwidget->setLayout(list);
      QScrollArea *scroll = new QScrollArea;
      scroll->setWidget(listwidget);
      outer->addWidget(scroll, layout::QBorderLayout::North);
      outer->addWidget(open_logger, layout::QBorderLayout::South);
      awards->setLayout(outer);
    }

    void qexperience_screen::refresh_expenses() const
    {
      qDeleteAll(expenses->children());
      delete expenses->layout();
      QFormLayout *list = new QFormLayout;
      layout::QBorderLayout* outer = new layout::QBorderLayout;

      for (auto purchase: _character->get_experience().purchases())
          list->addRow(character::narrative::EXPENSE_NAME.at(purchase.purchase_type()).c_str(),
                       label(purchase.purchase()->description()));

      QWidget *listwidget = new QWidget;
      listwidget->setLayout(list);

      QScrollArea *scroll = new QScrollArea;
      scroll->setWidget(listwidget);
      outer->addWidget(scroll, layout::QBorderLayout::North);

      expenses->setLayout(outer);
    }

} }
