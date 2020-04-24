#include "screen/qcraftingscreen.h"

#include "layout/qborderlayout.h"
#include <QStackedLayout>
#include <QVBoxLayout>

namespace qt {
  namespace screen {
    qcraftingscreen::qcraftingscreen(std::shared_ptr<manager::equipment_manager> mgr, QWidget *parent) : QWidget(parent), equip_manager(mgr)
    {
      QStackedLayout *stack = new QStackedLayout;

      new_weapon_project = new QPushButton("New Weapon Project");
      new_armor_project = new QPushButton("New Armor Project");
      new_material = new QPushButton("New Material");
      new_standard_weapon = new QPushButton("New Weapon");
      back = new QPushButton("Back");

      new_weapon_project_widget = new wizard::new_weapon_project;

      connect(new_weapon_project, &QPushButton::clicked, this, &qcraftingscreen::load_weapon_project);
      connect(new_weapon_project_widget, &wizard::new_weapon_project::project_created, this, &qcraftingscreen::on_project_created);
      connect(back, &QPushButton::clicked, this, &qcraftingscreen::back_issued);

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
      ((QStackedLayout*)layout())->setCurrentWidget(new_weapon_project_widget);
    }

    void qcraftingscreen::load_buttons_screen()
    {
      ((QStackedLayout*)layout())->setCurrentWidget(buttons_widget);
    }
  }
}
