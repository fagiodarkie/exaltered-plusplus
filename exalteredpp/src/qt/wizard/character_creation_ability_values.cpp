#include "wizard/character_creation_ability_values.h"

#include <QtDebug>

#include <QFormLayout>
#include <QGroupBox>
#include <QScrollArea>

#include "label/interfacelabels.h"
#include "layout/qborderlayout.h"
#include "layout/layout_constants.h"

namespace qt {
  namespace wizard {

    using namespace qt::labels::creation_wizard;
    using namespace qt::labels;

    character_creation_ability_values::character_creation_ability_values(QWidget *parent)
      : QWidget(parent) { }

    void character_creation_ability_values::ability_change(const character::ability_names::detailed_ability& detailed_ability, unsigned int new_value)
    {
      _abilities[detailed_ability.ability].set_ability_value(detailed_ability.declination, new_value);
      check_current_selection();
    }

    void character_creation_ability_values::set_current_abilities(const character::abilities& new_abilities,
                                                                  character::exalt::caste selected_caste,
                                                                  unsigned int number_of_caste_favorites,
                                                                  unsigned int number_of_free_favorites,
                                                                  unsigned int max_points,
                                                                  unsigned int min_in_favorites,
                                                                  unsigned int max_ability_value)
    {
      _abilities = new_abilities;
      _caste = selected_caste;
      caste_favorites = number_of_caste_favorites;
      free_favorites = number_of_free_favorites;
      max_ability_points = max_points;
      min_points_in_favorites = min_in_favorites;
      max_std_ability_value = max_ability_value;

      regenerate_abilities();

      check_current_selection();
    }

    void character_creation_ability_values::regenerate_abilities()
    {

      abilities = new QWidget;
      QVBoxLayout *ability_list = new QVBoxLayout;

      QMap<character::ability_names::ability_category, QGroupBox*> ability_groups;
      QMap<character::ability_names::ability_category, QFormLayout*> ability_forms;
      for (auto ab_category: character::ability_names::ABILITY_CATEGORIES)
        {
          QGroupBox *category_group = new QGroupBox(character::ability_names::ABILITY_CATEGORY_NAMES.at(ab_category).c_str());
          ability_groups[ab_category] = category_group;
          ability_list->addWidget(category_group);
          ability_forms[ab_category] = new QFormLayout;
        }

      for (auto ability_enum : character::ability_names::ABILITIES)
        {
          ability_value_row *row = new ability_value_row(_abilities[ability_enum]);
          row->add_rows(ability_forms[character::ability_names::CATEGORY_OF_ABILITY(ability_enum)]);
          row_of_ability.insert(ability_enum, row);
          //connect(row, &ability_value_row::ability_change, this, &character_creation_ability_values::ability_change);
        }

      for (auto ab_category: character::ability_names::ABILITY_CATEGORIES)
        ability_groups[ab_category]->setLayout(ability_forms[ab_category]);

      abilities->setLayout(ability_list);

      QScrollArea *scroll_abilities = new QScrollArea;
      scroll_abilities->setWidget(abilities);

      QHBoxLayout* buttons_layout = new QHBoxLayout;
      next_page = new QPushButton(NEXT_LABEL);
      cancel = new QPushButton(CANCEL_LABEL);
      buttons_layout->addWidget(cancel);
      buttons_layout->addWidget(next_page);

      next_page->setEnabled(false);
      connect(next_page, &QPushButton::clicked, this, &character_creation_ability_values::next_issued);
      connect(cancel, &QPushButton::clicked, this, &character_creation_ability_values::back_issued);

      QWidget* buttons = new QWidget;
      buttons->setLayout(buttons_layout);

      layout::QBorderLayout *outer_layout = new layout::QBorderLayout;
      outer_layout->addWidget(scroll_abilities, layout::QBorderLayout::Center);
      outer_layout->addWidget(buttons, layout::QBorderLayout::South);

      if (layout())
        delete layout();
      setLayout(outer_layout);
    }

    void character_creation_ability_values::check_current_selection()
    {
      unsigned int points_spent = 0, points_spent_in_favorites = 0;
      for (auto ability_enum : character::ability_names::ABILITIES)
        {
          //auto row = row_of_ability[ability_enum];
          //points_spent += row.value;
          //
          //if (row.is_favored)
          //  points_spent_in_favorites += row.value;
          //
          //row.increase->setEnabled(row.value < max_std_ability_value);
          //row.decrease->setEnabled(row.value > 0);
        }

      bool  should_inhibit_all_add = (points_spent == max_ability_points),
            // inhibit non favorites add if the only points left to spend are equal to the points we have to spend on favorites
            should_inhibit_non_favorites_add = (max_ability_points - points_spent == min_points_in_favorites - points_spent_in_favorites);

      for (auto ability_enum : character::ability_names::ABILITIES)
        {
          //auto row = row_of_ability[ability_enum];
          //row.increase->setEnabled(row.increase->isEnabled()
          //                         && !should_inhibit_all_add
          //                         && (row.is_favored || !should_inhibit_non_favorites_add));
        }

      next_page->setEnabled(max_ability_points == points_spent);
    }

    void character_creation_ability_values::next_issued()
    {
      for (auto ability: character::ability_names::ABILITIES)
        _abilities[ability] = row_of_ability[ability]->ability();

      emit abilities_chosen(_abilities);
    }

  }
}
