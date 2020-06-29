#include "screen/qcraftingscreen.h"

#include "layout/qborderlayout.h"
#include <QStackedLayout>
#include <QVBoxLayout>

#include "label/interfacelabels.h"
#include "equipment/craft/material.h"

namespace qt {
  namespace screen {
    qcraftingscreen::qcraftingscreen(std::shared_ptr<manager::equipment_manager> mgr, QWidget *parent) : QWidget(parent), equip_manager(mgr)
    {
      QStackedLayout *stack = new QStackedLayout;

      new_weapon_project = new QPushButton("New Weapon Project");
      new_armor_project = new QPushButton("New Armor Project");
      new_material = new QPushButton("New Material");
      new_standard_weapon = new QPushButton("New Weapon");

      list_weapon_project = new QPushButton("View Weapon Projects");
      list_armor_project = new QPushButton("View Armor Projects");
      list_material = new QPushButton("View Materials");
      list_standard_weapon = new QPushButton("View Weapons");

      back = new QPushButton(labels::BACK_LABEL);

      new_weapon_project_widget = new wizard::new_weapon_project;

      connect(new_weapon_project, &QPushButton::clicked, this, &qcraftingscreen::load_weapon_project);
      connect(new_weapon_project_widget, &wizard::new_weapon_project::project_created, this, &qcraftingscreen::on_project_created);
      connect(back, &QPushButton::clicked, this, &qcraftingscreen::back_issued);

      connect(list_material, &QPushButton::clicked, this, &qcraftingscreen::show_materials);
      connect(view_items, &wizard::view_edit_craft_items::edit_request, this, &qcraftingscreen::on_edit_issued);

      QVBoxLayout *buttons_layout = new QVBoxLayout;
      buttons_layout->addWidget(new_weapon_project);
      buttons_layout->addWidget(new_armor_project);
      buttons_layout->addWidget(new_material);
      buttons_layout->addWidget(new_standard_weapon);
      buttons_layout->addWidget(back);


      buttons_widget = new QWidget;
      buttons_widget->setLayout(buttons_layout);

      stack->addWidget(buttons_widget);
      stack->addWidget(new_weapon_project_widget);
      stack->addWidget(view_items);

      setLayout(stack);
      load_buttons_screen();
    }

    void qcraftingscreen::on_project_created(const equipment::craft::weapon_project &new_project)
    {
      equip_manager->add_project(new_project);
      load_buttons_screen();
    }

    void qcraftingscreen::load_weapon_project()
    {
      new_weapon_project_widget->reset();
      setCurrentWidget(new_weapon_project_widget);
    }

    void qcraftingscreen::load_buttons_screen()
    {
      setCurrentWidget(buttons_widget);
    }

    void qcraftingscreen::show_materials()
    {
      QList<QString> materials;
      for (auto m: equip_manager->materials())
        materials.append(m.name().c_str());

      view_items->update_items(materials, wizard::view_edit_craft_items::item_mode::material);
      setCurrentWidget(view_items);
    }

    void qcraftingscreen::on_edit_issued(const QString &item_name, wizard::view_edit_craft_items::item_mode item_type)
    {
      switch(item_type)
        {
        case wizard::view_edit_craft_items::item_mode::material:
          {
            equipment::craft::material old_material = equip_manager->get_material(item_name.toStdString());

          }
        }
    }
  }
}
