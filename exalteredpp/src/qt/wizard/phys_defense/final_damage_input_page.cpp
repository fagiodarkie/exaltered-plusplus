#include "wizard/phys_defense/final_damage_input_page.h"

#include "layout/qborderlayout.h"
#include "label/interfacelabels.h"
#include <QScrollArea>

namespace qt { namespace wizard {

    using namespace labels::wizards::physical_attack;

    final_damage_input_page::final_damage_input_page(QWidget *parent) : QWidget(parent)
    {
      layout::QBorderLayout *outer = new layout::QBorderLayout;

      status = new QLabel;

      provided_damage_box = new QSpinBox;
      provided_damage_box->setEnabled(false);
      roll_damage_radio = new QRadioButton(ROLL_DAMAGE_AUTOMATICALLY, this);
      roll_damage_radio->setChecked(true);
      provide_damage_radio = new QRadioButton(PROVIDE_DAMAGE_ROLL_RESULT, this);
      connect(provide_damage_radio, &QRadioButton::clicked, this, &final_damage_input_page::on_radio_change);
      connect(roll_damage_radio, &QRadioButton::clicked, this, &final_damage_input_page::on_radio_change);

      QVBoxLayout *vcenter = new QVBoxLayout;
      vcenter->addWidget(roll_damage_radio);
      vcenter->addWidget(provide_damage_radio);
      vcenter->addWidget(new QLabel(ROLLED_DAMAGE_RESULT));
      vcenter->addWidget(provided_damage_box);
      vcenter->setAlignment(Qt::AlignTop);
      QWidget* center_w = new QWidget;
      center_w->setLayout(vcenter);
      QScrollArea *scroll_w = new QScrollArea;
      scroll_w->setWidget(center_w);

      outer->addWidget(_progress_bar,     layout::QBorderLayout::North);
      outer->addWidget(scroll_w,          layout::QBorderLayout::Center);
      outer->addWidget(buttons_layout(),  layout::QBorderLayout::South);
      setLayout(outer);

      enable_next();
      on_next_issued([this]() { on_submit(); });
    }

    void final_damage_input_page::set_final_damage_pool(unsigned int post_soak_pool)
    {
      status->setText(FINAL_DAMAGE_SUMMARY.arg(post_soak_pool));
    }

    void final_damage_input_page::on_radio_change()
    {
      provided_damage_box->setEnabled(provide_damage_radio->isChecked());
    }

    void final_damage_input_page::on_submit()
    {
      if (roll_damage_radio->isChecked())
        emit roll_damage();
      else
        emit with_damage(provided_damage_box->value());
    }

}}
