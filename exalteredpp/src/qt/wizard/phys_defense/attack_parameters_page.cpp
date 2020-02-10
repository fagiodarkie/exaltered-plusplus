#include "wizard/phys_defense/attack_parameters_page.h"

#include "layout/qborderlayout.h"
#include <QFormLayout>
#include <QScrollArea>

#include "label/interfacelabels.h"

namespace qt { namespace wizard {

    using namespace labels::wizards::physical_attack;

    attack_parameters_page::attack_parameters_page()
    {
      layout::QBorderLayout *outer = new layout::QBorderLayout;

      precision_result_box = new QSpinBox;
      base_damage_box = new QSpinBox;
      base_damage_box->setMinimum(-15);
      min_damage_box = new QSpinBox;
      drill_box = new QSpinBox;

      damage_type_box = new QComboBox;
      for (auto damage: combat::DAMAGES)
        damage_type_box->addItem(combat::DAMAGE_NAME.at(damage).c_str(), static_cast<int>(damage));

      body_target_box = new QComboBox;
      for (auto target: combat::BODY_TARGET_LIST)
        body_target_box->addItem(combat::BODY_TARGET_NAME.at(target).c_str(), static_cast<int>(target));

      body_target_box->setCurrentText(combat::BODY_TARGET_NAME.at(combat::body_target::NO_TARGET).c_str());

      auto summary = new QLabel(DEFENSE_PRECISION_SUMMARY);

      QFormLayout *form = new QFormLayout;
      form->addRow(PRECISION_ROLL_RESULT, precision_result_box);
      form->addRow(ATTACK_FULL_BASE_DAMAGE, base_damage_box);
      form->addRow(WEAPON_DAMAGE_TYPE, damage_type_box);
      form->addRow(WEAPON_MIN_DAMAGE, min_damage_box);
      form->addRow(WEAPON_DRILL, drill_box);
      form->addRow(BODY_TARGET, body_target_box);
      QWidget* center_w = new QWidget;
      center_w->setLayout(form);
      QScrollArea *scroll_w = new QScrollArea;
      scroll_w->setWidget(center_w);

      QVBoxLayout *vcenter = new QVBoxLayout;
      vcenter->setAlignment(Qt::AlignTop);
      vcenter->addWidget(summary);
      vcenter->addWidget(scroll_w);
      QWidget* vwidget = new QWidget;
      vwidget->setLayout(vcenter);

      outer->addWidget(_progress_bar,     layout::QBorderLayout::North);
      outer->addWidget(vwidget,           layout::QBorderLayout::Center);
      outer->addWidget(buttons_layout(),  layout::QBorderLayout::South);
      setLayout(outer);

      enable_next();
      on_next_issued([this]() {
          auto damage = static_cast<combat::damage_type_enum>(damage_type_box->currentData().toInt());
          auto target = static_cast<combat::body_target>(body_target_box->currentData().toInt());
          emit attack_parameters(target, damage, precision_result_box->value(), base_damage_box->value(), min_damage_box->value(), drill_box->value());
        });
    }
}}
