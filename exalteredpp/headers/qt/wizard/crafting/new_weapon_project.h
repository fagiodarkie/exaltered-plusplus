#ifndef NEW_WEAPON_PROJECT_H
#define NEW_WEAPON_PROJECT_H

#include <QCheckBox>
#include <QComboBox>
#include <QPushButton>
#include <QSpinBox>
#include <QWidget>
#include <QStackedLayout>
#include <QTabWidget>
#include <QLineEdit>
#include "weapon_project_stat_widget.h"

#include "managers/equipment_manager.h"

namespace qt {
  namespace wizard {
    class new_weapon_project : public QWidget
    {
      Q_OBJECT
    public:
      explicit new_weapon_project(QWidget *parent = nullptr);

      void reset();

    signals:
      void project_created(const equipment::craft::weapon_project& new_project);
      void canceled_project();

    private:

      equipment::craft::weapon_project _project;
      QVector<equipment::craft::attack_type> _attack_types;

      equipment::craft::attack_type current_attack_type() const;

      QPushButton *attacks_chosen, *project_finished, *return_to_attack_definition, *back_to_craft_menu;

      QLineEdit *project_name;
      QComboBox *weapon_ability_box, *current_attack_info, *default_attack;
      QVector<QCheckBox*> attack_type_checkboxes;
      QWidget *attack_stat_screen, *attack_types_screen;
      QStackedLayout *all_screens;
      QSpinBox *weapon_hindrance, *weapon_bulk;
      QTabWidget *tabs;

      QMap<equipment::craft::attack_type, weapon_project_stat_widget*> stat_widgets;
      QMap<attribute::attribute_enum, QSpinBox*> attr_minimum;

      static const QString SELECTED_ENUM;

      void init_members();
      void check_name_attacks_valid();
      void name_chosen();
      void load_name_screen();
      void submit_project();

      QWidget* compose_stat_screen();
      QWidget* compose_attack_types_screen();

    };
  }
}



#endif // NEW_WEAPON_PROJECT_H
