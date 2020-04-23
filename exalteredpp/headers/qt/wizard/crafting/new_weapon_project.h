#ifndef NEW_WEAPON_PROJECT_H
#define NEW_WEAPON_PROJECT_H

#include <QCheckBox>
#include <QComboBox>
#include <QPushButton>
#include <QSpinBox>
#include <QWidget>
#include <QLineEdit>

#include "managers/equipment_manager.h"

namespace qt {
  namespace wizard {
    class new_weapon_project : public QWidget
    {
      Q_OBJECT
    public:
      explicit new_weapon_project(std::shared_ptr<manager::equipment_manager>, QWidget *parent = nullptr);


    private:

      std::shared_ptr<manager::equipment_manager> equip_manager;

      void on_attacks_chosen();
      void submit_project();

      equipment::craft::weapon_project _project;
      std::vector<combat::attack_attribute> _additional_attributes;
      QVector<equipment::craft::attack_type> _attack_types;

      equipment::craft::attack_type current_attack_type() const;

      QPushButton *attacks_chosen, *project_finished, *return_to_attack_definition;

      QLineEdit *project_name;
      QSpinBox *weapon_precision_spin, *weapon_damage_spin, *weapon_drill_spin, *weapon_min_spin;
      QComboBox *weapon_damage_box, *weapon_precision_attr_box, *weapon_damage_attr_box,
        *weapon_ability_box, *body_target_box, *current_attack_info, *default_attack;
      QVector<QCheckBox*> note_checkboxes, attack_type_checkboxes;
      QWidget *attack_stat_screen, *attack_types_screen;

      static const QString SELECTED_ENUM;

      void init_members();

      QWidget* compose_stat_screen();
      QWidget* compose_attack_types_screen();

    };
  }
}



#endif // NEW_WEAPON_PROJECT_H
