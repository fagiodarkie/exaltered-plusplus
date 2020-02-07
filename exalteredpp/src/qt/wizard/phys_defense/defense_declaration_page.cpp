#include "wizard/phys_defense/defense_declaration_page.h"

#include "layout/qborderlayout.h"

#include <QScrollArea>

namespace qt { namespace wizard {

    defense_declaration_page::defense_declaration_page(std::shared_ptr<character::character> defender,
                                                       const calculator::derived_value_calculator& calculator,
                                                       QWidget *parent)
      : QWidget(parent), _defender(defender), _calculator(calculator)
    {
      layout::QBorderLayout *outer = new layout::QBorderLayout;

      defense_box = new QComboBox;
      for (auto vd: combat::PHYSICAL_VD_LIST)
        defense_box->addItem(combat::VD_NAME.at(vd).c_str(), static_cast<int>(vd));
      connect(defense_box, &QComboBox::currentTextChanged, this, &defense_declaration_page::refresh_vd);

      weapon_defense_box = new QSpinBox;
      weapon_defense_box->setMinimum(-15);
      connect(weapon_defense_box, QOverload<int>::of(&QSpinBox::valueChanged), this, &defense_declaration_page::refresh_vd);

      parry_ability_box = new QComboBox;
      for (auto ability: _defender->abilities().keys())
        parry_ability_box->addItem(ability.name().c_str(), ability.serialise().c_str());
      connect(parry_ability_box, &QComboBox::currentTextChanged, this, &defense_declaration_page::refresh_vd);

      defense_info_label = new QLabel;

      vd_value_modifier = new QSpinBox;
      connect(vd_value_modifier, QOverload<int>::of(&QSpinBox::valueChanged), this, &defense_declaration_page::refresh_vd);
      vd_value_modifier->setMinimum(-15);

      counter_after_parry = new QCheckBox("Counter after your parry");
      connect(counter_after_parry, &QCheckBox::clicked, this, &defense_declaration_page::refresh_vd);

      refresh_vd();

      QVBoxLayout *vcenter = new QVBoxLayout;
      vcenter->addWidget(defense_info_label);
      vcenter->addWidget(new QLabel("VD value modifier:"));
      vcenter->addWidget(vd_value_modifier);
      vcenter->addWidget(defense_box);
      vcenter->addWidget(parry_ability_box);
      vcenter->addWidget(new QLabel("Weapon Defense:"));
      vcenter->addWidget(weapon_defense_box);
      vcenter->addWidget(counter_after_parry);
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

    void defense_declaration_page::refresh_vd()
    {
      auto vd = static_cast<combat::target_vd>(defense_box->currentData().toInt());
      if (vd == combat::target_vd::PHYSICAL_PARRY)
        {
          ability::ability_name ability = ability::ability_enum::WAR;
          ability.deserialise(parry_ability_box->currentData().toString().toStdString());

          _vd_value = _calculator.compute_physical_vd(*_defender, ability, weapon_defense_box->value()).parry_vd;

          counter_after_parry ->setEnabled(true);
          parry_ability_box   ->setEnabled(true);
          weapon_defense_box  ->setEnabled(true);
        }
      else
        {
          _vd_value = _calculator.compute_physical_vd(*_defender, ability::ability_enum::WAR).dodge_vd;
          counter_after_parry ->setEnabled(false);
          parry_ability_box   ->setEnabled(false);
          weapon_defense_box  ->setEnabled(false);
        }

      _countering = vd == combat::target_vd::PHYSICAL_PARRY && counter_after_parry->isChecked();

      _vd_value = dice::pool(_vd_value + vd_value_modifier->value() - (_countering ? 1 : 0));

      QString counter = _countering
          ? "\r\nAfter the parry, if successful, you will attempt a counter."
          : "";
      defense_info_label->setText(QString("You're defending with your %0 vd, with a final value of %1.%2")
                                  .arg(defense_box->currentText())
                                  .arg(_vd_value)
                                  .arg(counter));
    }

    void defense_declaration_page::on_submit()
    {
      auto vd = static_cast<combat::target_vd>(defense_box->currentData().toInt());
      if (vd == combat::target_vd::PHYSICAL_DODGE)
        {
          emit dodge(vd_value_modifier->value());
          return;
        }

      ability::ability_name ability = ability::ability_enum::WAR;
      ability.deserialise(parry_ability_box->currentData().toString().toStdString());

      emit parry(vd_value_modifier->value() + (_countering ? 0 : -1), ability, weapon_defense_box->value(), _countering);
    }
}}
