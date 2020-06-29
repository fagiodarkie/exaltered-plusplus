#pragma once

#include <QWidget>

#include "equipment/craft/material.h"
#include <QPushButton>
#include <QLineEdit>
#include <QComboBox>
#include <QSpinBox>
#include <QCheckBox>

namespace qt
{
  namespace wizard
  {
    class material_edit_screen : public QWidget
    {
      Q_OBJECT
    public:
      explicit material_edit_screen(QWidget *parent = nullptr);

      void with_material(const equipment::craft::material& m);
      void with_new_material();

    signals:
      void save_material(const equipment::craft::material& m);
      void back_issued();

    public slots:

    private:
      equipment::craft::material material;
      QPushButton* back;

      QLineEdit *name_edit;
      QCheckBox *changes_damage_type;

      QComboBox *category, *subcategory, *hardness, *overridden_damage_type;

      QSpinBox *craft_res_spin, *cost_spin, *availability_spin, *tenaciousness_spin, *break_spin, *slot_taken_spin, *minimum_damage_spin,
        *defense_bonus_spin, *precision_bonus_spin, *drill_bonus_spin, *im_bonus_spin;

      QMap<combat::damage_type_enum, QSpinBox*> damage_bonus_spin_for_dmg_type;

      void adjust_subcategory();
    };
  }
}
