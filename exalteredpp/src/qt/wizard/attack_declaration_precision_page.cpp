#include "wizard/attack_declaration_precision_page.h"

#include <QGroupBox>
#include <QScrollArea>

namespace qt {
  namespace wizard {

    attack_declaration_precision_page::attack_declaration_precision_page(std::shared_ptr<character::character> c, QWidget *parent)
      : QWidget(parent)
    {
      layout::QBorderLayout *outer = new layout::QBorderLayout;

      internal_bonus_spin = new QSpinBox;
      internal_bonus_spin->setMinimum(0);

      external_bonus_spin = new QSpinBox;
      external_bonus_spin->setMinimum(0);

      internal_malus_spin = new QSpinBox;
      internal_malus_spin->setMinimum(0);

      external_malus_spin = new QSpinBox;
      external_malus_spin->setMinimum(0);

      weapon_precision_spin = new QSpinBox;
      weapon_precision_spin->setMinimum(0);

      weapon_damage_spin = new QSpinBox;
      weapon_damage_spin->setMinimum(0);

      weapon_drill_spin = new QSpinBox;
      weapon_drill_spin->setMinimum(0);

      weapon_min_spin = new QSpinBox;
      weapon_min_spin->setMinimum(0);

      weapon_damage_attr_box = new QComboBox;
      for (auto attribute: attribute::ATTRIBUTES)
        weapon_damage_attr_box->addItem(attribute::ATTRIBUTE_NAME.at(attribute).c_str(), static_cast<int>(attribute));

      weapon_precision_attr_box = new QComboBox;
      for (auto attribute: attribute::ATTRIBUTES)
        weapon_precision_attr_box->addItem(attribute::ATTRIBUTE_NAME.at(attribute).c_str(), static_cast<int>(attribute));

      weapon_damage_box = new QComboBox;
      for (auto damagetype: combat::DAMAGES)
        weapon_damage_box->addItem(combat::DAMAGE_NAME.at(damagetype).c_str(), static_cast<int>(damagetype));

      weapon_ability_box = new QComboBox;
      for (auto ability: c->abilities().keys())
        weapon_ability_box->addItem(ability.name().c_str(), ability.serialise().c_str());

      for (auto attribute: combat::ATTACK_ATTRIBUTES)
        {
          auto check = new QCheckBox;
          check->setText(combat::ATTACK_ATTRIBUTE_NAME.at(attribute).c_str());
          check->setProperty("attack_attribute", static_cast<int>(attribute));
          attribute_checkboxes.append(check);
        }

      QFormLayout *weapon_form = new QFormLayout;
      weapon_form->addRow("Weapon Precision:", weapon_precision_spin);
      weapon_form->addRow("Weapon Damage:",    weapon_damage_spin);
      weapon_form->addRow("Weapon Minimum Damage:", weapon_min_spin);
      weapon_form->addRow("Weapon Drill:", weapon_drill_spin);
      weapon_form->addRow("Weapon Ability:", weapon_ability_box);
      weapon_form->addRow("Weapon Precision Attribute:", weapon_precision_attr_box);
      weapon_form->addRow("Weapon Damage Attribute:", weapon_damage_attr_box);
      weapon_form->addRow("Weapon Damage Type:", weapon_damage_box);
      QGroupBox *weapon_group = new QGroupBox("Weapon Stats");
      weapon_group->setLayout(weapon_form);

      QFormLayout *attack_form = new QFormLayout;
      attack_form->addRow("Internal Precision Bonus:", internal_bonus_spin);
      attack_form->addRow("Internal Precision Malus:", internal_malus_spin);
      attack_form->addRow("External Precision Bonus:", external_bonus_spin);
      attack_form->addRow("External Precision Malus:", external_malus_spin);
      for (auto checkbox: attribute_checkboxes)
        attack_form->addRow(checkbox);
      QGroupBox *attack_group = new QGroupBox("Attack Stats");
      attack_group->setLayout(attack_form);

      QVBoxLayout *center = new QVBoxLayout;
      center->addWidget(weapon_group);
      center->addWidget(attack_group);
      QWidget* center_widget = new QWidget;
      center_widget->setLayout(center);
      QScrollArea *scroll = new QScrollArea;
      scroll->setWidget(center_widget);

      outer->addWidget(_progress_bar,     layout::QBorderLayout::North);
      outer->addWidget(scroll,            layout::QBorderLayout::Center);
      outer->addWidget(buttons_layout(),  layout::QBorderLayout::South);
      setLayout(outer);

      enable_next();
      on_next_issued([this]() {this->collect_weapon_and_attributes(); });
    }

    void attack_declaration_precision_page::collect_weapon_and_attributes()
    {
      equip::weapon created_weapon;
      ability::ability_name weapon_ability(ability::ability_enum::WAR);
      weapon_ability.deserialise(weapon_ability_box->currentData().toString().toStdString());
      created_weapon.with_precision(weapon_precision_spin->value())
          .with_base_damage(weapon_damage_spin->value())
          .with_min_damage(weapon_min_spin->value())
          .with_drill(weapon_drill_spin->value())
          .use_with(weapon_ability)
          .requires_for_precision(static_cast<attribute::attribute_enum>(weapon_precision_attr_box->currentData().toInt()))
          .uses_for_damage(static_cast<attribute::attribute_enum>(weapon_damage_attr_box->currentData().toInt()))
          .with_damage_type(static_cast<combat::damage_type_enum>(weapon_damage_box->currentData().toInt()));

      std::vector<combat::attack_attribute> attack_attributes;
      for (auto attack_check: attribute_checkboxes)
        if (attack_check->isChecked())
          attack_attributes.push_back(static_cast<combat::attack_attribute>(attack_check->property("attack_attribute").toInt()));

      emit attack_selected(created_weapon, attack_attributes,
                           internal_bonus_spin->value(), internal_malus_spin->value(),
                           external_bonus_spin->value(), external_malus_spin->value());
    }

  }
}
