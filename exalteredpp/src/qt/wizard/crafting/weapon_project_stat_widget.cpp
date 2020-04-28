#include "wizard/crafting/weapon_project_stat_widget.h"

#include <QFormLayout>
#include <QGroupBox>
#include <layout/qborderlayout.h>
#include "label/interfacelabels.h"

namespace qt {
  namespace wizard {

    using namespace labels::wizards::physical_attack;

    weapon_project_stat_widget::weapon_project_stat_widget(QWidget *parent) : QWidget(parent)
    {
      weapon_precision_spin = new QSpinBox;
      weapon_damage_spin = new QSpinBox;
      weapon_drill_spin = new QSpinBox;
      weapon_min_spin = new QSpinBox;
      weapon_im_spin = new QSpinBox;
      weapon_cadence_spin = new QSpinBox;
      weapon_range_spin = new QSpinBox;

      for (auto spin: { weapon_min_spin, weapon_precision_spin, weapon_damage_spin, weapon_drill_spin, weapon_im_spin, weapon_range_spin })
        spin->setMinimum(-99);
      weapon_cadence_spin->setMinimum(1);

      for (auto note: equipment::craft::NOTES)
        {
          auto check = new QCheckBox;
          check->setText(equipment::craft::NOTE_NAME.at(note).c_str());
          check->setProperty("note", static_cast<int>(note));
          note_checkboxes.push_back(check);
        }

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

      QFormLayout *weapon_form = new QFormLayout;
      weapon_form->addRow(WEAPON_ENCUMBRANCE   , weapon_im_spin);
      weapon_form->addRow(WEAPON_PRECISION     , weapon_precision_spin);
      weapon_form->addRow(WEAPON_DAMAGE        , weapon_damage_spin);
      weapon_form->addRow(WEAPON_MIN_DAMAGE    , weapon_min_spin);
      weapon_form->addRow(WEAPON_CADENCE       , weapon_cadence_spin);
      weapon_form->addRow(WEAPON_DRILL         , weapon_drill_spin);
      weapon_form->addRow(WEAPON_PRECISION_ATTR, weapon_precision_attr_box);
      weapon_form->addRow(WEAPON_DAMAGE_ATTR   , weapon_damage_attr_box);
      weapon_form->addRow(WEAPON_DAMAGE_TYPE   , weapon_damage_box);

      QGroupBox *weapon_group = new QGroupBox(WEAPON_STATS_TITLE);
      weapon_group->setLayout(weapon_form);

      int attack_rows = note_checkboxes.size() / 2;
      QGridLayout *grid = new QGridLayout;
      for (int i = 0; i < attack_rows; ++i)
        {
          grid->addWidget(note_checkboxes[2 * i    ], i, 0);
          grid->addWidget(note_checkboxes[2 * i + 1], i, 1);
        }
      if (note_checkboxes.size() % 2 != 0)
        grid->addWidget(note_checkboxes[attack_rows * 2], attack_rows, 0);

      QGroupBox *attack_group = new QGroupBox(NOTES_TITLE);
      attack_group->setLayout(grid);

      layout::QBorderLayout *outer = new layout::QBorderLayout;
      outer->addWidget(weapon_group, layout::QBorderLayout::Center);
      outer->addWidget(attack_group, layout::QBorderLayout::South);

      setLayout(outer);
    }

    equipment::craft::attack_stat weapon_project_stat_widget::stat() const
    {
      equipment::craft::attack_stat result;
      result._im = weapon_im_spin->value();
      result._range = weapon_range_spin->value();
      result._drill = weapon_drill_spin->value();
      result._precision = weapon_precision_spin->value();
      result._damage = weapon_damage_spin->value();
      result._cadence = weapon_cadence_spin->value();
      result._damage_type = static_cast<combat::damage_type_enum>(weapon_damage_box->currentData().toInt());
      result._precision_attribute = static_cast<attribute::attribute_enum>(weapon_precision_attr_box->currentData().toInt());
      result._damage_attribute = static_cast<attribute::attribute_enum>(weapon_damage_attr_box->currentData().toInt());
      for (auto note_check: note_checkboxes)
        if (note_check->isChecked())
          result._notes.push_back(static_cast<equipment::craft::note>(note_check->property("note").toInt()));

      return result;
    }
  }
}
