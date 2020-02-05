#include "wizard/provide_balance_details_page.h"

#include "layout/qborderlayout.h"

namespace qt {
  namespace wizard {

    provide_balance_details_page::provide_balance_details_page()
    {
      layout::QBorderLayout *outer = new layout::QBorderLayout;

      status_label = new QLabel;
      status_label->setWordWrap(true);

      balance_spin = new QSpinBox;
      balance_spin->setMinimum(0);

      QVBoxLayout *center = new QVBoxLayout;
      center->addWidget(status_label);
      center->addWidget(balance_spin);
      center->setAlignment(Qt::AlignTop);
      QWidget *center_widget = new QWidget;
      center_widget->setLayout(center);

      outer->addWidget(_progress_bar, layout::QBorderLayout::North);
      outer->addWidget(center_widget, layout::QBorderLayout::Center);
      outer->addWidget(buttons_layout(), layout::QBorderLayout::South);

      setLayout(outer);

      enable_next();
      on_next_issued([this]() { emit balance_chosen(balance_spin->value()); });
    }

    void provide_balance_details_page::remind_chosen_vd(combat::target_vd vd)
    {
      status_label->setText(QString("The defender defended with his %0 vd. What is its balance?")
                            .arg(combat::VD_NAME.at(vd).c_str()));
    }
}
}
