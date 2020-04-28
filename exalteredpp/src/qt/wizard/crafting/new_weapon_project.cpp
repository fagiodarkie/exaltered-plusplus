#include "wizard/crafting/new_weapon_project.h"

#include <QFormLayout>
#include <QGroupBox>
#include <QScrollArea>

#include "layout/qborderlayout.h"
#include "layout/layout_helper_factories.h"
#include "label/interfacelabels.h"
#include "widget/std_compatible.h"

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
      scroll->setSizePolicy(QSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding));
      scroll->setWidgetResizable(true);

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
      weapon_hindrance = new QSpinBox;
      weapon_bulk = new QSpinBox;

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

      for (auto att: attribute::ATTRIBUTES)
        attr_minimum[att] = new QSpinBox;

      project_name = new QLineEdit;

      attacks_chosen = new QPushButton(labels::craft_wizard::ATTACKS_CHOSEN);
      attacks_chosen->setEnabled(false);
      project_finished = new QPushButton(labels::craft_wizard::PROJECT_FINISHED);
      return_to_attack_definition = new QPushButton(labels::BACK_LABEL);
      back_to_craft_menu = new QPushButton(labels::BACK_TO_MENU_LABEL);

      connect(attacks_chosen,               &QPushButton::clicked, this, &new_weapon_project::name_chosen);
      connect(project_finished,             &QPushButton::clicked, this, &new_weapon_project::submit_project);
      connect(project_name,                 &QLineEdit::textChanged, this, &new_weapon_project::check_name_attacks_valid);
      connect(back_to_craft_menu,           &QPushButton::clicked, [this]() { emit canceled_project(); });
      connect(return_to_attack_definition,  &QPushButton::clicked, this, &new_weapon_project::load_name_screen);
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

      for (auto c: attr_minimum)
        c->setValue(0);

      weapon_hindrance->setValue(0);
      weapon_bulk->setValue(0);

      _attack_types.clear();
      current_attack_info->clear();
      default_attack->clear();
    }

    QWidget* new_weapon_project::compose_attack_types_screen()
    {
      QFormLayout *project_name_form = new QFormLayout;
      project_name_form->addRow(project_name);

      QGroupBox *name_group = new QGroupBox(labels::craft_wizard::PROJECT_NAME);
      name_group->setLayout(project_name_form);

      QGroupBox *attacks_group = new QGroupBox(labels::craft_wizard::ATTACKS);

      int attack_rows = attack_type_checkboxes.size() / 2;
      QGridLayout *grid = new QGridLayout;
      for (int i = 0; i < attack_rows; ++i)
        {
          grid->addWidget(attack_type_checkboxes[2 * i    ], i, 0);
          grid->addWidget(attack_type_checkboxes[2 * i + 1], i, 1);
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
      tabs->addTab(new weapon_project_stat_widget, "temp"); // for sizing purposes.

      QFormLayout *weapon_form = new QFormLayout;
      weapon_form->addRow(WEAPON_ABILITY   , weapon_ability_box);
      weapon_form->addRow(WEAPON_HINDRANCE, weapon_hindrance);
      weapon_form->addRow(WEAPON_BULK, weapon_bulk);
      weapon_form->addRow(labels::craft_wizard::DEFAULT_ATTACK, default_attack);

      QGroupBox *minimums_group = new QGroupBox(labels::craft_wizard::MINIMUMS_GROUP);

      QGridLayout *grid = new QGridLayout;
      int row = 0;
      for (auto att_cat: attribute::ATTRIBUTE_CATEGORIES)
        {
          int column = 0;
          for (auto att: attribute::ATTRIBUTES_BY_CATEGORY.at(att_cat))
            {
              grid->addWidget(layout::form_row(label(attribute::ATTRIBUTE_NAME.at(att)), attr_minimum[att]), row, column);
              ++column;
            }
          ++row;
        }
      minimums_group->setLayout(grid);
      minimums_group->setSizePolicy(QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding));

      QGroupBox *lower_group = new QGroupBox(labels::craft_wizard::STATS);
      lower_group->setLayout(weapon_form);

      layout::QBorderLayout *center = new layout::QBorderLayout;
      center->addWidget(lower_group, layout::QBorderLayout::North);
      center->addWidget(tabs, layout::QBorderLayout::Center);
      center->addWidget(minimums_group, layout::QBorderLayout::South);
      tabs->setSizePolicy(QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding));
      QWidget* ats = new QWidget;
      ats->setLayout(center);
      ats->setSizePolicy(QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding));

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

      for (auto attr: attribute::ATTRIBUTES)
        if (attr_minimum[attr]->value() > 0)
          weapon_project.requires_attribute(attr, attr_minimum[attr]->value());

      if (weapon_hindrance->value() > 0)
        weapon_project.with_hindrance(weapon_hindrance->value());

      if (weapon_bulk->value() > 0)
        weapon_project.with_bulk(weapon_bulk->value());

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
