#include "wizard/character_creation_ability_values.h"

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
    }

    void character_creation_ability_values::regenerate_abilities()
    {
      abilities = new QWidget;
      summary = new QLabel;
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

          connect(row, &ability_value_row::ability_change, this, &character_creation_ability_values::on_ability_change);
          connect(row, &ability_value_row::new_declination, this, &character_creation_ability_values::on_new_declination);

          row->add_rows(ability_forms[character::ability_names::CATEGORY_OF_ABILITY(ability_enum)]);
          row_of_ability[ability_enum] = row;
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

      QVBoxLayout *upper = new QVBoxLayout;
      upper->setAlignment(Qt::AlignTop);
      upper->addWidget(_progress_bar);
      upper->addWidget(summary);
      QWidget* upper_widget = new QWidget;
      upper_widget->setLayout(upper);

      layout::QBorderLayout *outer_layout = new layout::QBorderLayout;
      outer_layout->addWidget(upper_widget, layout::QBorderLayout::North);
      outer_layout->addWidget(scroll_abilities, layout::QBorderLayout::Center);
      outer_layout->addWidget(buttons, layout::QBorderLayout::South);

      on_ability_change();

      if (layout())
        delete layout();
      setLayout(outer_layout);
    }

    void character_creation_ability_values::on_new_declination()
    {
      for (auto ability: character::ability_names::ABILITIES)
        _abilities[ability] = row_of_ability[ability]->ability();

      regenerate_abilities();
    }

    validation_result character_creation_ability_values::check_current_selection()
    {
      QMap<character::ability_names::detailed_ability, operation_enabled> result;
      unsigned int points_spent = 0, points_spent_in_favorites = 0, favorite_abilities = 0, caste_favorite_abilities = 0;
      auto caste_abilities = character::exalt::exalt_caste::get_caste(_caste).abilities();
      for (auto ability_enum : character::ability_names::ABILITIES)
        {
          auto row = row_of_ability[ability_enum];
          for (auto actual_ability: row->ability().get_ability_names())
            {
              auto ability = row->ability().get_ability(actual_ability.declination);
              points_spent += ability.get_ability_value();
              bool caste_ability = std::find(caste_abilities.begin(), caste_abilities.end(), ability_enum) != caste_abilities.end();
              if (ability.is_favourite())
                {
                  points_spent_in_favorites += ability.get_ability_value();
                  if (caste_ability)
                    ++caste_favorite_abilities;
                  else
                    ++favorite_abilities;
                }
              result[actual_ability].decrease = ability.get_ability_value() > 0;
              result[actual_ability].increase = ability.get_ability_value() < max_std_ability_value;
            }
        }

      bool  should_inhibit_all_add = (points_spent == max_ability_points),
              // inhibit non favorites add if the only points left to spend are equal to the points we have to spend on favorites
              should_inhibit_non_favorites_add = (max_ability_points - points_spent == min_points_in_favorites - points_spent_in_favorites);

      for (auto ability_enum : character::ability_names::ABILITIES)
        {
          auto row = row_of_ability[ability_enum];
          for (auto actual_ability: row->ability().get_ability_names())
            {
              auto ability = row->ability().get_ability(actual_ability.declination);
              bool caste_ability = std::find(caste_abilities.begin(), caste_abilities.end(), ability_enum) != caste_abilities.end();

              result[actual_ability].increase &= (!should_inhibit_all_add);
              if (!ability.is_favourite())
                result[actual_ability].increase &= (!should_inhibit_non_favorites_add);

              result[actual_ability].favorite = !ability.is_favourite()
                                                && ((!caste_ability && favorite_abilities < free_favorites)
                                                    || (caste_ability && caste_favorite_abilities < caste_favorites));
              result[actual_ability].unfavorite = ability.is_favourite()
                                                && (!caste_ability || row->ability().has_abilities());
            }
        }

      validation_result check;
      check.operations = result;
      check.total_spent = points_spent;
      check.total_spent_in_favorites = points_spent_in_favorites;
      check.remaining_favorites = free_favorites - favorite_abilities;
      check.remaining_caste_favorites = caste_favorites - caste_favorite_abilities;

      return check;
    }

    void character_creation_ability_values::on_ability_change()
    {
      auto validation = check_current_selection();

      QString text = "Overall points spent: %1 / %2.\r\n"
                     "Points spent in favored abilities: %3 / %4.\r\n"
                     "Caste abilities to favor left: %5.\r\n"
                     "Abilities to favor left: %6.";

      summary->setWordWrap(true);
      summary->setText(text.arg(validation.total_spent).arg(max_ability_points)
                       .arg(validation.total_spent_in_favorites).arg(min_points_in_favorites)
                       .arg(validation.remaining_caste_favorites).arg(validation.remaining_favorites));

      bool points = (max_ability_points == validation.total_spent),
          free_fav = (validation.remaining_favorites == 0),
          caste_fav = (validation.remaining_caste_favorites == 0);

      next_page->setEnabled(points && free_fav && caste_fav);

      for (auto ability: validation.operations.keys())
        {
          auto op = validation.operations[ability];
          row_of_ability[ability.ability]->update_operations(ability.declination, op.increase, op.decrease, op.favorite, op.unfavorite);

        }
    }

    void character_creation_ability_values::next_issued()
    {
      for (auto ability: character::ability_names::ABILITIES)
        _abilities[ability] = row_of_ability[ability]->ability();

      emit abilities_chosen(_abilities);
    }

  }
}
