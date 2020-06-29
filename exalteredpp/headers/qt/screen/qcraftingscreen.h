#ifndef QCRAFTINGSCREEN_H
#define QCRAFTINGSCREEN_H

#include <QWidget>
#include <QPushButton>
#include <QComboBox>

#include "wizard/crafting/new_weapon_project.h"
#include "wizard/crafting/view_edit_craft_items.h"
#include "wizard/crafting/material_edit_screen.h"

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
      QPushButton *new_weapon_project, *new_armor_project, *new_material, *new_standard_weapon,
        *list_weapon_project, *list_armor_project, *list_material, *list_standard_weapon,
        *back;

      wizard::new_weapon_project *new_weapon_project_widget;
      wizard::view_edit_craft_items *view_items;
      wizard::material_edit_screen *material_edit_screen;
      std::shared_ptr<manager::equipment_manager> equip_manager;
      QWidget* buttons_widget;

      void on_project_created(const equipment::craft::weapon_project& new_weapon_project);

      void load_buttons_screen();
      void load_weapon_project();

      void show_materials();
      void create_material();

      void on_edit_issued(const QString& item_name, wizard::view_edit_craft_items::item_mode item_type);

      inline void setCurrentWidget(QWidget* w)
      {
        ((QStackedLayout*)layout())->setCurrentWidget(w);
      }
    };

  }
}

#endif // QCRAFTINGSCREEN_H
