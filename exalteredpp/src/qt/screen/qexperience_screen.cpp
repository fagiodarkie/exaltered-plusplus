#include "screen/qexperience_screen.h"
#include "layout/qborderlayout.h"
#include "caste_style.h"

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
      qt::style::foreground(open_logger);

      open_expense_logger = new QPushButton("Add expense");
      _purchase_logger = new widget::experience_purchase_widget(_character, this);
      connect(open_expense_logger, &QPushButton::clicked, _purchase_logger, &QDialog::show);
      connect(_purchase_logger, &widget::experience_purchase_widget::purchased, this, &qexperience_screen::add_expense);
      qt::style::foreground(open_expense_logger);

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

    qexperience_screen::~qexperience_screen()
    {
      qt::style::forget(open_logger);
      qt::style::forget(open_expense_logger);
    }

    void qexperience_screen::recompute_logger_session()
    {
      _logger->set_next_session_number(_character->experience().last_session() + 1);
    }

    void qexperience_screen::update_status_label() const
    {
      unsigned int total_cost = _character->experience().total_cost(),
          total_award = _character->experience().total_awarded(),
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

      _purchase_logger->set_available_experience(remaining);
      open_expense_logger->setEnabled(remaining > 0);
    }

    void qexperience_screen::add_expense(const narrative::experience_purchase &purchase)
    {
      _purchase_logger->hide();
      _character->experience().purchase(purchase);
      purchase.purchase()->apply(_character);
      _character_manager.save_character(_character);

      delete expenses->layout();
      update_status_label();
      refresh_expenses();
    }

    void qexperience_screen::add_session(const narrative::session_awards& new_awards)
    {
      _character->experience().award(new_awards);

      _character_manager.save_character(_character);

      _logger->set_next_session_number(_character->experience().last_session() + 1);
      _logger->hide();

      delete awards->layout();
      update_status_label();
      refresh_awards();
    }

    void qexperience_screen::refresh()
    {
      refresh_awards();
      refresh_expenses();
    }

    void qexperience_screen::refresh_awards()
    {
      awards_vbox = new QVBoxLayout;
      awards_scroll = new QScrollArea;

      awards_buttons = new QWidget;
      awards_buttons->setLayout(new QVBoxLayout);
      awards_buttons->layout()->addWidget(open_logger);

      QWidget *listwidget = new QWidget;
      layout::QBorderLayout* outer = new layout::QBorderLayout;

      for (unsigned int i = 0; i <= _character->experience().last_session(); ++i)
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
      auto entries = _character->experience().awards_on_session(session_number);
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
      delete expenses->layout();

      QGridLayout *list = new QGridLayout;
      layout::QBorderLayout* outer = new layout::QBorderLayout;

      int row = 0;
      for (auto purchase: _character->experience().purchases())
        {
          list->addWidget(label(narrative::EXPENSE_NAME.at(purchase.purchase_type())), row, 0);
          list->addWidget(label(purchase.purchase()->description()), row, 1, 1, 3);
          list->addWidget(new QLabel(QString::number(purchase.cost())), row, 4);

          ++row;
        }

      QWidget *listwidget = new QWidget;
      listwidget->setLayout(list);

      QScrollArea *scroll = new QScrollArea(expenses);
      scroll->setWidget(listwidget);
      outer->addWidget(scroll, layout::QBorderLayout::Center);

      QVBoxLayout *button_layout = new QVBoxLayout;
      button_layout->addWidget(open_expense_logger);
      QWidget* button_widget_outer = new QWidget;
      button_widget_outer->setLayout(button_layout);
      outer->addWidget(button_widget_outer, layout::QBorderLayout::South);

      expenses->setLayout(outer);
    }

} }
