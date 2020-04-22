#include "wizard/crafting/new_weapon_project.h"

#include <QFormLayout>
#include <QGroupBox>
#include <QScrollArea>
#include "layout/qborderlayout.h"

#include "label/interfacelabels.h"
namespace qt {
  namespace wizard {

    const QString new_weapon_project::SELECTED_ENUM = "selected_enum";

    using namespace labels::wizards::physical_attack;

    new_weapon_project::new_weapon_project(std::shared_ptr<manager::equipment_manager> mgr, QWidget *parent) : QWidget(parent), equip_manager(mgr)
    {
      layout::QBorderLayout *outer = new layout::QBorderLayout;

      weapon_precision_spin = new QSpinBox;
      weapon_precision_spin->setMinimum(0);

      weapon_damage_spin = new QSpinBox;
      weapon_damage_spin->setMinimum(0);

      weapon_drill_spin = new QSpinBox;
      weapon_drill_spin->setMinimum(0);

      weapon_min_spin = new QSpinBox;
      weapon_min_spin->setMinimum(0);

      weapon_damage_attr_box = new QComboBox;
      weapon_precision_attr_box = new QComboBox;
      for (auto attribute: attribute::ATTRIBUTES)
        {
          weapon_damage_attr_box->addItem(attribute::ATTRIBUTE_NAME.at(attribute).c_str(), (std::underlying_type_t<attribute::attribute_enum>)attribute);
          weapon_precision_attr_box->addItem(attribute::ATTRIBUTE_NAME.at(attribute).c_str(), (std::underlying_type_t<attribute::attribute_enum>)attribute);
        }

      weapon_damage_box = new QComboBox;
      for (auto damagetype: combat::DAMAGES)
        weapon_damage_box->addItem(combat::DAMAGE_NAME.at(damagetype).c_str(), (std::underlying_type_t<combat::damage_type_enum>)damagetype);

      for (auto attack_type: equipment::craft::ATTACK_TYPES)
        {
          auto c = new QCheckBox(equipment::craft::ATTACK_TYPE_NAMES.at(attack_type).c_str());
          c->setProperty(SELECTED_ENUM.toStdString().c_str(), (std::underlying_type_t<equipment::craft::attack_type>)attack_type);
          attack_type_checkboxes.append(c);
        }

      weapon_ability_box = new QComboBox;

      for (auto ability: ability::COMBAT_ABILITIES)
        weapon_ability_box->addItem(ability::ABILITY_NAME.at(ability).c_str(), ability::ability_name(ability).serialise().c_str());

      body_target_box = new QComboBox;
      for (auto body: combat::BODY_TARGET_LIST)
        body_target_box->addItem(combat::BODY_TARGET_NAME.at(body).c_str(), static_cast<int>(body));
      body_target_box->setCurrentText(combat::BODY_TARGET_NAME.at(combat::body_target::NO_TARGET).c_str());

      // this for notes
      // for (auto attribute: combat::ATTACK_ATTRIBUTES)
      //   {
      //     auto check = new QCheckBox;
      //     check->setText(combat::ATTACK_ATTRIBUTE_NAME.at(attribute).c_str());
      //     check->setProperty("attack_attribute", static_cast<int>(attribute));
      //     attribute_checkboxes.append(check);
      //   }

      QFormLayout *weapon_form = new QFormLayout;
      weapon_form->addRow(WEAPON_PRECISION     , weapon_precision_spin);
      weapon_form->addRow(WEAPON_DAMAGE        , weapon_damage_spin);
      weapon_form->addRow(WEAPON_MIN_DAMAGE    , weapon_min_spin);
      weapon_form->addRow(WEAPON_DRILL         , weapon_drill_spin);
      weapon_form->addRow(WEAPON_ABILITY       , weapon_ability_box);
      weapon_form->addRow(WEAPON_PRECISION_ATTR, weapon_precision_attr_box);
      weapon_form->addRow(WEAPON_DAMAGE_ATTR   , weapon_damage_attr_box);
      weapon_form->addRow(WEAPON_DAMAGE_TYPE   , weapon_damage_box);
      QGroupBox *weapon_group = new QGroupBox(WEAPON_STATS_TITLE);
      weapon_group->setLayout(weapon_form);

      QFormLayout *attack_form = new QFormLayout;
      attack_form->addRow(BODY_TARGET, body_target_box);

      for (auto checkbox: note_checkboxes)
        attack_form->addRow(checkbox);

      QGroupBox *attack_group = new QGroupBox(ATTACK_STATS_TITLE);
      attack_group->setLayout(attack_form);

      QVBoxLayout *center = new QVBoxLayout;
      center->addWidget(weapon_group);
      center->addWidget(attack_group);
      QWidget* center_widget = new QWidget;
      center_widget->setLayout(center);
      QScrollArea *scroll = new QScrollArea;
      scroll->setWidget(center_widget);

      attacks_chosen = new QPushButton("These are the project's attack types");
      project_finished = new QPushButton("Submit project");

      QWidget* buttons = new QWidget;
      QVBoxLayout *lower_buttons = new QVBoxLayout;
      lower_buttons->addWidget(attacks_chosen);
      lower_buttons->addWidget(project_finished);
      project_finished->hide();
      buttons->setLayout(lower_buttons);

      outer->addWidget(scroll,     layout::QBorderLayout::Center);
      outer->addWidget(buttons,    layout::QBorderLayout::South);
      setLayout(outer);

    }

    void new_weapon_project::submit_project()
    {
      equipment::craft::weapon_project weapon_project;
      ability::ability_name weapon_ability(ability::ability_enum::WAR);
      weapon_ability.deserialise(weapon_ability_box->currentData().toString().toStdString());
      weapon_project.with_precision(weapon_precision_spin->value())
          .with_base_damage(weapon_damage_spin->value())
          .with_min_damage(weapon_min_spin->value())
          .with_drill(weapon_drill_spin->value())
          .use_with(weapon_ability)
          .requires_for_precision(static_cast<attribute::attribute_enum>(weapon_precision_attr_box->currentData().toInt()))
          .uses_for_damage(static_cast<attribute::attribute_enum>(weapon_damage_attr_box->currentData().toInt()))
          .with_damage_type(static_cast<combat::damage_type_enum>(weapon_damage_box->currentData().toInt()));

      equip_manager->add_project(weapon_project);

    }
  }
}
