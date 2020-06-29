#include "wizard/crafting/material_edit_screen.h"

#include "label/interfacelabels.h"
#include "equipment/craft/material.h"

namespace qt
{
  namespace wizard
  {


    material_edit_screen::material_edit_screen(QWidget *parent) : QWidget(parent)
    {
      back = new QPushButton(labels::BACK_LABEL);
      connect(back, &QPushButton::clicked, this, &material_edit_screen::back_issued);

      name_edit = new QLineEdit;
      changes_damage_type = new QCheckBox;

      category = new QComboBox;
      for (auto c: equipment::craft::MATERIAL_CATEGORIES)
          category->addItem(equipment::craft::NAME_OF_MATERIAL_CATEGORY.at(c).c_str(), std::underlying_type_t<equipment::craft::material_category>(c));
      connect(category, &QComboBox::currentTextChanged, this, &material_edit_screen::adjust_subcategory);

      subcategory = new QComboBox;
      adjust_subcategory();

      hardness = new QComboBox;
      for (auto h: equipment::craft::TYPES_OF_HARDNESS)
        hardness->addItem(equipment::craft::MATERIAL_HARDNESS_NAME.at(h).c_str(), std::underlying_type_t<equipment::craft::hardness_enum>(h));

      overridden_damage_type = new QComboBox;
      for (auto dt: combat::DAMAGES)
        hardness->addItem(combat::DAMAGE_NAME.at(dt).c_str(), std::underlying_type_t<combat::damage_type_enum>(dt));

      craft_res_spin      = new QSpinBox;
      cost_spin           = new QSpinBox;
      availability_spin   = new QSpinBox;
      tenaciousness_spin  = new QSpinBox;
      break_spin          = new QSpinBox;
      slot_taken_spin     = new QSpinBox;
      minimum_damage_spin = new QSpinBox;
      defense_bonus_spin  = new QSpinBox;
      precision_bonus_spin = new QSpinBox;
      drill_bonus_spin    = new QSpinBox;
      im_bonus_spin       = new QSpinBox;




    }

    void material_edit_screen::with_material(const equipment::craft::material &m)
    {
      material = m;
    }

    void material_edit_screen::with_new_material()
    {
      material = equipment::craft::material();
    }

    void material_edit_screen::adjust_subcategory()
    {
      auto cat = static_cast<equipment::craft::material_category>(category->currentData().toInt());
      auto subcats = equipment::craft::SUBCATEGORIES_OF_CATEGORY.at(cat);
      subcategory->clear();
      if (!subcats.empty())
        {
          subcategory->setEnabled(true);
          for (auto subc: subcats)
            subcategory->addItem(equipment::craft::NAME_OF_MATERIAL_SUBCATEGORY.at(subc).c_str(), std::underlying_type_t<equipment::craft::submaterial_category>(subc));
        }
      else
        {
          subcategory->setEnabled(false);
        }
    }
  }
}
