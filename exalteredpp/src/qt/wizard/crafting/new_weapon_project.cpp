#include "wizard/crafting/new_weapon_project.h"

#include <QFormLayout>
#include <QGroupBox>
#include <QScrollArea>
#include "layout/qborderlayout.h"

#include "label/interfacelabels.h"
namespace qt {
  namespace wizard {

    const QString new_weapon_project::SELECTED_ENUM = "selected_enum";

    using namespace labels::wizards::physical_attack;

    new_weapon_project::new_weapon_project(QWidget *parent) : QWidget(parent)
    {
      layout::QBorderLayout *outer = new layout::QBorderLayout;

      init_members();

      attack_stat_screen = compose_stat_screen();
      attack_types_screen = compose_attack_types_screen();

      all_screens = new QStackedLayout;
      all_screens->addWidget(attack_types_screen);
      all_screens->addWidget(attack_stat_screen);
      QWidget* center_widget = new QWidget;
      center_widget->setLayout(all_screens);
      QScrollArea *scroll = new QScrollArea;
      scroll->setWidget(center_widget);

      QWidget* buttons = new QWidget;
      QVBoxLayout *lower_buttons = new QVBoxLayout;
      lower_buttons->addWidget(attacks_chosen);
      lower_buttons->addWidget(return_to_attack_definition);
      lower_buttons->addWidget(project_finished);
      lower_buttons->addWidget(back_to_craft_menu);
      buttons->setLayout(lower_buttons);

      outer->addWidget(scroll,     layout::QBorderLayout::Center);
      outer->addWidget(buttons,    layout::QBorderLayout::South);
      setLayout(outer);

      load_name_screen();
    }

    void new_weapon_project::init_members()
    {
      current_attack_info = new QComboBox;
      default_attack = new QComboBox;

      for (auto attack_type: equipment::craft::ATTACK_TYPES)
        {
          auto c = new QCheckBox(equipment::craft::ATTACK_TYPE_NAMES.at(attack_type).c_str());
          c->setProperty(SELECTED_ENUM.toStdString().c_str(), (std::underlying_type_t<equipment::craft::attack_type>)attack_type);
          connect(c, &QCheckBox::stateChanged, this, &new_weapon_project::check_name_attacks_valid);
          attack_type_checkboxes.push_back(c);
        }

      weapon_ability_box = new QComboBox;

      for (auto ability: ability::COMBAT_ABILITIES)
        weapon_ability_box->addItem(ability::ABILITY_NAME.at(ability).c_str(), ability::ability_name(ability).serialise().c_str());

      project_name = new QLineEdit;

      // this for notes
      // for (auto attribute: combat::ATTACK_ATTRIBUTES)
      //   {
      //     auto check = new QCheckBox;
      //     check->setText(combat::ATTACK_ATTRIBUTE_NAME.at(attribute).c_str());
      //     check->setProperty("attack_attribute", static_cast<int>(attribute));
      //     attribute_checkboxes.append(check);
      //   }

      attacks_chosen = new QPushButton("These are the project's attack types");
      attacks_chosen->setEnabled(false);
      project_finished = new QPushButton("Submit project");
      return_to_attack_definition = new QPushButton("Back");
      back_to_craft_menu = new QPushButton("Back to main menu");

      connect(attacks_chosen, &QPushButton::clicked, this, &new_weapon_project::name_chosen);
      connect(project_finished, &QPushButton::clicked, this, &new_weapon_project::submit_project);
      connect(project_name, &QLineEdit::textChanged, this, &new_weapon_project::check_name_attacks_valid);
      connect(back_to_craft_menu, &QPushButton::clicked, [this]() { emit canceled_project(); });
    }

    void new_weapon_project::check_name_attacks_valid()
    {
      bool has_attack = std::accumulate(attack_type_checkboxes.begin(), attack_type_checkboxes.end(), false, [](bool s, QCheckBox* checkbox) {
          return s || checkbox->isChecked();
        });
      attacks_chosen->setEnabled(has_attack && !project_name->text().isEmpty());
    }

    void new_weapon_project::reset()
    {
      project_name->setText("");

      for (auto c: attack_type_checkboxes)
        c->setChecked(false);

      stat_widgets.clear();
      tabs->clear();

      _attack_types.clear();
      current_attack_info->clear();
      default_attack->clear();
    }

    QWidget* new_weapon_project::compose_attack_types_screen()
    {
      QFormLayout *project_name_form = new QFormLayout;
      project_name_form->addRow("Project name:", project_name);

      QGroupBox *name_group = new QGroupBox("Weapon Name");
      name_group->setLayout(project_name_form);

      QGroupBox *attacks_group = new QGroupBox("Attacks");

      int attack_rows = attack_type_checkboxes.size() / 2;
      QGridLayout *grid = new QGridLayout;
      for (int i = 0; i < attack_rows; ++i)
        {
          grid->addWidget(attack_type_checkboxes[2*i  ], i, 0);
          grid->addWidget(attack_type_checkboxes[2*i+1], i, 1);
        }
      if (attack_type_checkboxes.size() % 2 != 0)
        grid->addWidget(attack_type_checkboxes[attack_rows * 2], attack_rows, 0);

      attacks_group->setLayout(grid);

      QVBoxLayout *attack_types_layout = new QVBoxLayout;
      attack_types_layout->setAlignment(Qt::AlignTop);
      attack_types_layout->addWidget(name_group);
      attack_types_layout->addWidget(attacks_group);

      QWidget* result = new QWidget;
      result->setLayout(attack_types_layout);
      return result;
    }

    QWidget* new_weapon_project::compose_stat_screen()
    {
      tabs = new QTabWidget;

      QFormLayout *weapon_form = new QFormLayout;
      weapon_form->addRow(WEAPON_ABILITY   , weapon_ability_box);
      weapon_form->addRow("Default attack:", default_attack);

      QGroupBox *lower_group = new QGroupBox("General stats");
      lower_group->setLayout(weapon_form);


      QVBoxLayout *center = new QVBoxLayout;
      center->addWidget(lower_group);
      center->addWidget(tabs);
      QWidget* ats = new QWidget;
      ats->setLayout(center);

      return ats;
    }

    equipment::craft::attack_type new_weapon_project::current_attack_type() const
    {
      if (current_attack_info == nullptr || current_attack_info->count() == 0)
        return equipment::craft::attack_type::DEFAULT;

      return static_cast<equipment::craft::attack_type>(current_attack_info->currentData().toInt());
    }

    void new_weapon_project::submit_project()
    {
      equipment::craft::weapon_project weapon_project;
      ability::ability_name weapon_ability(ability::ability_enum::WAR);
      weapon_ability.deserialise(weapon_ability_box->currentData().toString().toStdString());
      weapon_project.with_name(project_name->text().toStdString())
          .usually_attacks_with(static_cast<equipment::craft::attack_type>(default_attack->currentData().toInt()))
          .use_with(weapon_ability);

      for (auto atk: stat_widgets.keys())
          weapon_project.with_stat(stat_widgets[atk]->stat(), atk);

      emit project_created(weapon_project);

    }

    void new_weapon_project::load_name_screen()
    {
      all_screens->setCurrentWidget(attack_types_screen);
      return_to_attack_definition->hide();
      project_finished->hide();
      attacks_chosen->show();
      back_to_craft_menu->show();
    }

    void new_weapon_project::name_chosen()
    {
      stat_widgets.clear();
      tabs->clear();

      default_attack->clear();

      for (auto check : attack_type_checkboxes)
        if (check->isChecked())
          {
            auto atk_type = static_cast<equipment::craft::attack_type>(check->property(SELECTED_ENUM.toStdString().c_str()).toInt());
            stat_widgets[atk_type] = new weapon_project_stat_widget;
            tabs->addTab(stat_widgets[atk_type], check->text());
            default_attack->addItem(check->text(), static_cast<std::underlying_type_t<equipment::craft::attack_type>>(atk_type));
          }

      all_screens->setCurrentWidget(attack_stat_screen);
      return_to_attack_definition->show();
      project_finished->show();
      attacks_chosen->hide();
      back_to_craft_menu->hide();
    }
  }
}
