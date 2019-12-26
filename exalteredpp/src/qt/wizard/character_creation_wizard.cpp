#include "wizard/character_creation_wizard.h"

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
      for (auto attribute_e : attribute_names::ATTRIBUTES)
        attributes[attribute_e] = attribute(attribute_names::ATTRIBUTE_NAME.at(attribute_e), 1);

      for (auto ability_e : ability_names::ABILITIES)
        {
          if (ability_names::has_declination(ability_e))
              abilities[ability_e] = ability_group(ability_e, {} );
          else
            abilities[ability_e] = ability_group(ability_e);
        }

      name_page = new character_creation_name_type_page(this);
      connect(name_page, &character_creation_name_type_page::back_issued, this, &character_creation_wizard::fallback);
      connect(name_page, &character_creation_name_type_page::character_type_chosen, this, &character_creation_wizard::load_attributes_priority);

      attribute_priority_page = new attributes_priority_page(this);
      connect(attribute_priority_page, &attributes_priority_page::back_issued, this, &character_creation_wizard::fallback);
      connect(attribute_priority_page, &attributes_priority_page::attributes_chosen, this, &character_creation_wizard::load_attributes_values);

      attribute_points_page = new character_creation_attribute_points_page(this);
      connect(attribute_points_page, &character_creation_attribute_points_page::back_issued, this, &character_creation_wizard::fallback);
      connect(attribute_points_page, &character_creation_attribute_points_page::attribute_points_chosen, this, &character_creation_wizard::load_attribute_points);

      favorite_abilities_page = new character_creation_favorite_abilities(this);
      connect(favorite_abilities_page, &character_creation_favorite_abilities::back_issued, this, &character_creation_wizard::fallback);
      connect(favorite_abilities_page, &character_creation_favorite_abilities::abilities_selected, this, &character_creation_wizard::load_favored_abilities);

      abilities_page = new character_creation_ability_values(this);
      connect(abilities_page, &character_creation_ability_values::back_issued, this, &character_creation_wizard::fallback);
      connect(abilities_page, &character_creation_ability_values::ability_points_chosen, this, &character_creation_wizard::load_ability_values);

      virtues_page = new character_creation_virtues_vice(this);
      connect(virtues_page, &character_creation_virtues_vice::back_issued, this, &character_creation_wizard::fallback);
      connect(virtues_page, &character_creation_virtues_vice::virtues_chosen, this, &character_creation_wizard::load_virtues);

      persona_page = new character_creation_persona(this);
      connect(persona_page, &character_creation_persona::back_issued, this, &character_creation_wizard::fallback);
      connect(persona_page, &character_creation_persona::persona_created, this, &character_creation_wizard::load_persona);

      layout = new QStackedLayout;
      layout->addWidget(name_page);
      layout->addWidget(attribute_priority_page);
      layout->addWidget(attribute_points_page);
      layout->addWidget(favorite_abilities_page);
      layout->addWidget(abilities_page);
      layout->addWidget(virtues_page);
      layout->addWidget(persona_page);

      setLayout(layout);
    }

    void character_creation_wizard::load_attributes_priority(const QString&  char_name, creation::character_type type, exalt::caste selected_caste)
    {
      new_character_type = type;
      character_name = char_name;
      caste = selected_caste;
      character_model = creation::character_type_model::get_by_character_type(type);

      power.get_logos().set_logos(calculator.starting_logos(type));
      power.get_essence().set_khan(calculator.starting_khan(type));
      power.get_essence().set_permanent_essence(calculator.starting_essence(type));

      attribute_priority_page->set_attribute_values(static_cast<int>(character_model.primary_category_attribute_value),
                                                    static_cast<int>(character_model.secondary_category_attribute_value),
                                                    static_cast<int>(character_model.tertiary_category_attribute_value));

      advance();
    }

    void character_creation_wizard::load_attributes_values(const QString& primary_attribute, const QString& secondary_attribute, const QString& tertiary_attribute)
    {
      points_per_category.clear();
      points_per_category.insert(attribute_names::ATTRIBUTE_CATEGORY_BY_NAME(primary_attribute  .toStdString()), character_model.primary_category_attribute_value);
      points_per_category.insert(attribute_names::ATTRIBUTE_CATEGORY_BY_NAME(secondary_attribute.toStdString()), character_model.secondary_category_attribute_value);
      points_per_category.insert(attribute_names::ATTRIBUTE_CATEGORY_BY_NAME(tertiary_attribute .toStdString()), character_model.tertiary_category_attribute_value);

      attribute_points_page->set_total_points(points_per_category);
      attribute_points_page->set_current_attributes(attributes);

      advance();
    }

    void character_creation_wizard::load_attribute_points(const class attributes &points)
    {
      attributes = points;

      favorite_abilities_page->set_current_abilities(abilities, caste, character_model.caste_abilities, character_model.favored_abilities);

      advance();
    }

    void character_creation_wizard::load_favored_abilities(const QList<ability_names::detailed_ability> &favored_abilities)
    {
      // reset
      for (auto ability: ability_names::ABILITIES)
        for (auto declination: abilities[ability].get_abilities())
          abilities[ability].set_favourite(false, declination.get_name());

      for (auto ability: favored_abilities)
        {
          abilities[ability.ability].set_favourite(true, ability.declination);
        }

      abilities_page->set_current_abilities(abilities, character_model.starting_ability_points, character_model.min_ability_points_on_favorite_abilities, character_model.max_std_ability_points_on_creation);

      advance();
    }

    void character_creation_wizard::load_ability_values(const class abilities &abilities)
    {
      this->abilities = abilities;

      virtues_page->update_virtues_limits(character_virtues, character_model.starting_virtue_points, character_model.max_std_virtue_points);

      advance();
    }

    void character_creation_wizard::load_virtues(const virtues &virtues)
    {
      character_virtues = virtues;
      persona.set_persona(calculator.compute_persona(new_character_type, attributes, power.get_willpower(), power.get_essence()));

      persona_page->set_current_persona(virtues, persona, character_model, attributes, power);

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
                              power);

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
