#include "screen/qexperience_screen.h"
#include "layout/qborderlayout.h"

#include <QTabWidget>
#include <QFormLayout>
#include <QGroupBox>
#include "widget/std_compatible.h"

namespace qt { namespace screen {

    qexperience_screen::qexperience_screen(std::shared_ptr<character::character> character,
                                           manager::character_manager &ch_manager,
                                           QWidget *parent) : QWidget(parent), _character(character), _character_manager(ch_manager)
    {
      open_logger = new QPushButton("Add session");

      _logger = new widget::session_experience_logger(this);

      connect(open_logger, &QPushButton::clicked, _logger, &QDialog::show);
      connect(_logger, &widget::session_experience_logger::session_logged, this, &qexperience_screen::add_session);

      layout::QBorderLayout *outer = new layout::QBorderLayout;

      status = new QLabel;
      update_status_label();

      awards = new QWidget;

      expenses = new QWidget;
      listexpenses = new QWidget;

      refresh();

      QTabWidget *center = new QTabWidget;
      center->setTabPosition(QTabWidget::TabPosition::North);
      center->addTab(expenses, "Experience Purchases");
      center->addTab(awards, "Experience Awards");

      outer->addWidget(status, layout::QBorderLayout::North);
      outer->addWidget(center, layout::QBorderLayout::Center);

      recompute_logger_session();
      setLayout(outer);
    }

    void qexperience_screen::recompute_logger_session()
    {
      _logger->set_next_session_number(_character->get_experience().last_session() + 1);
    }

    void qexperience_screen::update_status_label() const
    {
      unsigned int total_cost = _character->get_experience().total_cost(),
          total_award = _character->get_experience().total_awarded(),
          remaining = total_award - total_cost;
      auto text = QString("Experience spent: %1\r\n"
                          "Total Experience: %2\r\n"
                          "Remaining Experience: %3")
          .arg(total_cost)
          .arg(total_award)
          .arg(remaining);
      status->setText(text);
      status->setMargin(2);
      status->adjustSize();
    }

    void qexperience_screen::add_session(const character::narrative::session_awards& new_awards)
    {
      _character->get_experience().award(new_awards);

      _character_manager.save_character(_character);

      _logger->set_next_session_number(_character->get_experience().last_session() + 1);
      _logger->hide();

      delete awards->layout();

      refresh_awards();
    }

    void qexperience_screen::refresh()
    {
      refresh_awards();
      refresh_expenses();
    }

    void qexperience_screen::refresh_awards()
    {
      listawards = new QWidget;
      awards_vbox = new QVBoxLayout;
      awards_scroll = new QScrollArea;

      awards_buttons = new QWidget;
      awards_buttons->setLayout(new QVBoxLayout);
      awards_buttons->layout()->addWidget(open_logger);

      QWidget *listwidget = new QWidget;
      layout::QBorderLayout* outer = new layout::QBorderLayout;

      for (unsigned int i = 0; i <= _character->get_experience().last_session(); ++i)
        {
          add_award_list(i);
        }

      listwidget->setLayout(awards_vbox);
      listwidget->adjustSize();
      awards_scroll->setWidget(listwidget);
      outer->addWidget(awards_scroll, layout::QBorderLayout::Center);

      outer->addWidget(awards_buttons, layout::QBorderLayout::South);
      awards->setLayout(outer);
    }

    void qexperience_screen::add_award_list(unsigned int session_number) const
    {
      auto entries = _character->get_experience().awards_on_session(session_number);
      if (entries.empty())
        return;

      QGroupBox *session_group = new QGroupBox(QString("Session #%1").arg(session_number));
      session_group->setMinimumWidth(130);

      QVBoxLayout *inner = new QVBoxLayout;
      for (auto entry: entries)
        {
          if (entry.second.amount() == 0)
            continue;

          auto summary = label(entry.second.summary());
          summary->setWordWrap(true);
          summary->setMinimumWidth(120);
          summary->setSizePolicy(QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding));
          inner->addWidget(summary);
          summary->adjustSize();
        }

      session_group->setLayout(inner);
      session_group->adjustSize();
      session_group->setSizePolicy(QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding));
      awards_vbox->addWidget(session_group);
    }

    void qexperience_screen::refresh_expenses()
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

      QScrollArea *scroll = new QScrollArea(expenses);
      scroll->setWidget(listwidget);
      outer->addWidget(scroll, layout::QBorderLayout::North);

      expenses->setLayout(outer);
    }

} }
