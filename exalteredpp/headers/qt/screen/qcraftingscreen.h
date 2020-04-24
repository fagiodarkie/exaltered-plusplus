#ifndef QCRAFTINGSCREEN_H
#define QCRAFTINGSCREEN_H

#include <QWidget>
#include <QPushButton>

#include "wizard/crafting/new_weapon_project.h"

namespace qt {
  namespace screen {
    class qcraftingscreen : public QWidget
    {
      Q_OBJECT
    public:
      explicit qcraftingscreen(std::shared_ptr<manager::equipment_manager>, QWidget *parent = nullptr);

    signals:
      void back_issued();

    private:
      QPushButton *new_weapon_project, *new_armor_project, *new_material, *new_standard_weapon, *back;

      wizard::new_weapon_project *new_weapon_project_widget;
      std::shared_ptr<manager::equipment_manager> equip_manager;
      QWidget* buttons_widget;

      void on_project_created(const equipment::craft::weapon_project& new_weapon_project);

      void load_buttons_screen();
      void load_weapon_project();
    };

  }
}

#endif // QCRAFTINGSCREEN_H
