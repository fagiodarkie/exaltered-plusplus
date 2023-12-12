#pragma once

#include <QWidget>
#include "widget/with_next_continue_buttons.h"
#include "widget/with_progress_bar.h"
#include "widget/with_next_continue_buttons.h"
#include "widget/with_progress_bar.h"
#include "combat/physical_attack.h"
#include "character.h"

#include <QComboBox>
#include <QSpinBox>
#include <QFormLayout>
#include "layout/qborderlayout.h"
#include <QCheckBox>

namespace qt {
  namespace wizard {

    class attack_declaration_precision_page : public QWidget, public widget::with_progress_bar, public widget::with_next_back_buttons
    {
      Q_OBJECT
    public:
      explicit attack_declaration_precision_page(std::shared_ptr<character::character> c, QWidget *parent = nullptr);

    signals:
      void attack_selected(const equipment::weapon& weapon, const std::vector<combat::attack_attribute>& attributes,
                           int internal_bonus, int external_bonus, combat::body_target target);

    private:
      equipment::weapon _weapon;
      std::vector<combat::attack_attribute> _additional_attributes;

      QSpinBox *internal_bonus_spin, *external_bonus_spin,
        *weapon_precision_spin, *weapon_damage_spin, *weapon_drill_spin, *weapon_min_spin;
      QComboBox *weapon_damage_box, *weapon_precision_attr_box, *weapon_damage_attr_box, *weapon_ability_box, *body_target_box;
      QVector<QCheckBox*> attribute_checkboxes;

      void collect_weapon_and_attributes();
    };

}
}