#include "wizard/character_creation_ability_values.h"

#include <QFormLayout>
#include <QGroupBox>

#include "label/interfacelabels.h"
#include "layout/qborderlayout.h"

namespace qt {
  namespace wizard {

    using namespace qt::labels::creation_wizard;
    using namespace qt::labels;

    ability_value_row::ability_value_row(character::ability_names::ability_enum ability, character::ability_names::ability_category category, const QString& ability_name)
      : ability(ability), category(category), ability_name(ability_name)
    {
      label = new QLabel;
      increase = new QPushButton("+");
      increase->resize(increase->minimumHeight(), increase->minimumHeight());
      decrease = new QPushButton("-");
      decrease->resize(increase->minimumHeight(), increase->minimumHeight());
    }

    QWidget* ability_value_row::widget() const
    {
      QWidget* result = new QWidget;

      QHBoxLayout *buttons = new QHBoxLayout;
      buttons->addWidget(decrease);
      buttons->addWidget(increase);
      result->setLayout(buttons);

      return result;
    }

    void ability_value_row::update(character::ability_group ability)
    {
      value = ability.get_ability();
      is_favored = ability.is_favourite();

      label->setText(labels::creation_wizard::ATTRIBUTE_WITH_POINTS(ability_name, value));
      if (is_favored)
        label->setStyleSheet("font-weight: bold");
    }

    character_creation_ability_values::character_creation_ability_values(QWidget *parent)
      : QWidget(parent)
    {

      QWidget* abilities = new QWidget;
      QVBoxLayout *ability_list = new QVBoxLayout;

      QMap<character::ability_names::ability_category, QGroupBox*> ability_groups;
      QMap<character::ability_names::ability_category, QFormLayout*> ability_forms;
      for (auto ab_category: character::ability_names::ABILITY_CATEGORIES)
        {
          QGroupBox *category_group = new QGroupBox(character::ability_names::ABILITY_CATEGORY_NAMES[ab_category]);
          ability_groups[ab_category] = category_group;
          ability_list->addWidget(category_group);
        }

      for (auto ability_enum : character::ability_names::ABILITIES)
        {
          ability_value_row row(ability_enum, character::ability_names::CATEGORY_OF_ABILITY(ability_enum), character::ability_names::ABILITY_NAME[ability_enum]);
          ability_forms[character::ability_names::CATEGORY_OF_ABILITY(ability_enum)]->addRow(row.label, row.widget());
          row_of_ability[ability_enum] = row;
          // TODO connections
        }

      for (auto ab_category: character::ability_names::ABILITY_CATEGORIES)
        ability_groups[ab_category]->setLayout(ability_forms[ab_category]);

      abilities->setLayout(ability_list);

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
      outer_layout->addWidget(abilities, layout::QBorderLayout::Center);
      outer_layout->addWidget(buttons, layout::QBorderLayout::South);

      setLayout(outer_layout);
    }

    void character_creation_ability_values::set_current_abilities(const character::abilities &new_abilities, unsigned int number_of_default_favorites, unsigned int number_of_favorite_abilities)
    {
      _abilities = new_abilities;
      default_favorite = number_of_default_favorites;
      max_favorite = number_of_favorite_abilities;

      for (auto ability_enum : character::ability_names::ABILITIES)
        {
          row_of_ability[ability_enum].update(_abilities[ability_enum]);
        }

      check_current_selection();
    }

    void character_creation_ability_values::check_current_selection()
    {
      next_page->setEnabled(false);
    }

    void character_creation_ability_values::next_issued()
    {
      emit ability_points_chosen(_abilities);
    }

  }
}
