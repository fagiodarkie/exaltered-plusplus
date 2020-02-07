#include "wizard/chargen/character_creation_wizard.h"

#include <QLabel>
#include <QStackedWidget>

namespace qt {
  namespace wizard {

    using character::character;
    using namespace character;

    character_creation_wizard::character_creation_wizard(manager::character_manager &manager, calculator::worker::abstract_calculator_worker& worker, QWidget* parent)
      : QWidget (parent),
        character_model(::character::creation::character_type_model::SOLAR_EXALT),
        char_manager(manager),
        calculator(worker)
    {
      // initialise character specs
      for (auto attribute_e : attribute::ATTRIBUTES)
        attributes[attribute_e] = 1;

      for (auto ability_e : ability::ABILITIES)
        {
          if (ability::has_declination(ability_e))
            {
              for (auto declination : ability::ability_declination::DECLINATIONS_OF_ABILITY.at(ability_e))
                abilities.add(ability::ability(ability::ability_name(ability_e, declination)));
            }
          else
            abilities.add(ability::ability(ability_e));
        }

      name_page = new character_creation_name_type_page(this);
      name_page->on_back_issued([this]() { fallback(); });
      connect(name_page, &character_creation_name_type_page::character_type_chosen, this, &character_creation_wizard::load_attributes_priority);

      attribute_priority_page = new attributes_priority_page(this);
      attribute_priority_page->on_back_issued([this]() { fallback(); });
      connect(attribute_priority_page, &attributes_priority_page::attributes_chosen, this, &character_creation_wizard::load_attributes_values);

      attribute_points_page = new character_creation_attribute_points_page(this);
      attribute_points_page->on_back_issued([this]() { fallback(); });
      connect(attribute_points_page, &character_creation_attribute_points_page::attribute_points_chosen, this, &character_creation_wizard::load_attribute_points);

      abilities_page = new character_creation_ability_values(this);
      abilities_page->on_back_issued([this]() { fallback(); });
      connect(abilities_page, &character_creation_ability_values::abilities_chosen, this, &character_creation_wizard::load_ability_values);

      virtues_page = new character_creation_virtues_vice(this);
      virtues_page->on_back_issued([this]() { fallback(); });
      connect(virtues_page, &character_creation_virtues_vice::virtues_chosen, this, &character_creation_wizard::load_virtues);

      persona_page = new character_creation_persona(this);
      persona_page->on_back_issued([this]() { fallback(); });
      connect(persona_page, &character_creation_persona::persona_created, this, &character_creation_wizard::load_persona);

      layout = new QStackedLayout;
      QList<QWidget*> pages = { name_page, attribute_priority_page, attribute_points_page, abilities_page, virtues_page, persona_page };

      for (unsigned int i = 0; i < pages.size(); ++i)
        {
          layout->addWidget(pages.at(i));
          dynamic_cast<widget::with_progress_bar*>(pages.at(i))->set_progress_bar_status(i, pages.size());
        }

      setLayout(layout);
    }

    void character_creation_wizard::load_attributes_priority(const QString&  char_name, creation::character_type type, exalt::caste selected_caste)
    {
      new_character_type = type;
      character_name = char_name;
      caste = selected_caste;
      character_model = creation::character_type_model::get_by_character_type(type);

      logos.set_logos(calculator.starting_logos(type));
      essence.set_khan(calculator.starting_khan(type));
      essence.set_permanent_essence(calculator.starting_essence(type));

      attribute_priority_page->set_values(static_cast<int>(character_model.primary_category_attribute_value),
                                                    static_cast<int>(character_model.secondary_category_attribute_value),
                                                    static_cast<int>(character_model.tertiary_category_attribute_value));

      advance();
    }

    void character_creation_wizard::load_attributes_values(const QString& primary_attribute, const QString& secondary_attribute, const QString& tertiary_attribute)
    {
      points_per_category.clear();
      points_per_category.insert(attribute::ATTRIBUTE_CATEGORY_BY_NAME(primary_attribute  .toStdString()), character_model.primary_category_attribute_value);
      points_per_category.insert(attribute::ATTRIBUTE_CATEGORY_BY_NAME(secondary_attribute.toStdString()), character_model.secondary_category_attribute_value);
      points_per_category.insert(attribute::ATTRIBUTE_CATEGORY_BY_NAME(tertiary_attribute .toStdString()), character_model.tertiary_category_attribute_value);

      attribute_points_page->set_total_points(points_per_category);
      attribute_points_page->set_current_attributes(attributes);

      advance();
    }

    void character_creation_wizard::load_attribute_points(const attribute::attributes &points)
    {
      attributes = points;

      for (auto fav_ability : exalt::exalt_caste::get_caste(caste).abilities())
        {
          // take a default declination
          auto declination = ability::has_declination(fav_ability)
              ? ability::ability_declination::DECLINATIONS_OF_ABILITY.at(fav_ability).at(0)
              : ability::ability_declination::NO_DECLINATION;

          // if there is no favorite ability, set one.
          bool has_at_least_one = false;
          for (auto ab: abilities.with_type(fav_ability))
            if (ab.favored())
              {
                has_at_least_one = true;
                break;
              }

          if (!has_at_least_one)
            abilities[ability::ability_name(fav_ability, declination)].set_favored();

        }

      abilities_page->set_current_abilities(abilities, caste, character_model.caste_abilities, character_model.favored_abilities,
                                            character_model.starting_ability_points, character_model.min_ability_points_on_favorite_abilities, character_model.max_std_ability_points_on_creation);

      advance();
    }

    void character_creation_wizard::load_ability_values(const class ability::abilities &abilities)
    {
      this->abilities = abilities;

      virtues_page->update_virtues_limits(character_virtues, character_model.starting_virtue_points, character_model.max_std_virtue_points);

      advance();
    }

    void character_creation_wizard::load_virtues(const virtues::virtues &virtues)
    {
      character_virtues = virtues;
      persona.set_persona(calculator.compute_persona(new_character_type, attributes, willpower, essence));

      persona_page->set_current_persona(virtues, persona, character_model, attributes);

      advance();
    }

    void character_creation_wizard::load_persona(const social::persona &persona)
    {
      this->persona = persona;

      advance();
    }

    void character_creation_wizard::advance()
    {
      if (layout->currentIndex() + 1 < layout->count() )
        {
          layout->setCurrentIndex(layout->currentIndex() + 1);
        }
      else
        {
          auto final_character =
              char_manager.create_character(calculator, character_name.toStdString(),
                              new_character_type,
                              caste,
                              attributes,
                              abilities,
                              character_virtues,
                              essence, willpower, health, logos);

          emit character_created(final_character);
        }
    }

    void character_creation_wizard::fallback()
    {
      if (layout->currentIndex() > 0)
        layout->setCurrentIndex(layout->currentIndex() -1);
      else
        emit back_issued();
    }
  }
}
