#include "abilities/ability_group.h"
#include "ability_not_found_exception.h"
#include "invalid_parameter.h"
#include "json_constants.h"

#include <algorithm>

namespace ability
{
    ability_group::ability_group(ability_enum ability_e, std::vector<ability> abilities, std::vector<specialisation> existing_specialisations)
      : macro_ability(ability_e), actual_abilities(abilities), specialisations(existing_specialisations)
    { }

    ability_group::ability_group(const ability_group& o)
      : macro_ability(o.macro_ability), actual_abilities(o.actual_abilities), specialisations(o.specialisations)
    { }

    ability_group& ability_group::operator=(const ability_group& o)
    {
      macro_ability = o.macro_ability;
      actual_abilities = o.actual_abilities;
      specialisations = o.specialisations;
      return *this;
    }

    ability_enum ability_group::get_ability_enum() const
    {
      return macro_ability;
    }

    std::string ability_group::get_name() const
    {
      return ABILITY_NAME.at(macro_ability);
    }

    std::vector<ability> ability_group::get_abilities() const
    {
      auto group_name = get_name();
      if (!has_abilities())
        return { ability(group_name, get_ability(ability_declination::NO_DECLINATION).get_ability_value()) };

      std::vector<ability> mod_abilities;
      for (ability a : actual_abilities)
        {
          auto m_ability = ability(group_name + " (" + a.name() + ")", a.get_ability_value());
          m_ability.set_favourite(a.is_favourite());
          mod_abilities.push_back(m_ability);
        }

      return mod_abilities;
    }

    std::vector<specialisation> ability_group::get_specialisations() const
    {
      return specialisations;
    }

    ability_category ability_group::get_category() const
    {
      return CATEGORY_OF_ABILITY(macro_ability);
    }

    ability ability_group::get_ability(const std::string& name) const
    {
      for (ability ab : actual_abilities)
        {
          if (ab.name() == name)
            return ab;
        }
      throw exception::ability_not_found_exception();
    }

    specialisation ability_group::get_specialisation(const std::string& name) const
    {
      for (specialisation spec : specialisations)
        {
          if (spec.name() == name)
            return spec;
        }
      throw exception::ability_not_found_exception();
    }

    bool ability_group::has_ability(const std::string& ability_name) const
    {      
      auto found_ability = std::find_if(actual_abilities.begin(), actual_abilities.end(),
        [ability_name] (ability ab)
        {
          return ab.name() == ability_name;
        });

      return found_ability != actual_abilities.end();
    }

    bool ability_group::has_specialisation(const std::string& specialisation_name) const
    {
      auto found_spec = std::find_if(specialisations.begin(), specialisations.end(),
         [specialisation_name] (specialisation spec)
         {
           return spec.name() == specialisation_name;
         });

      return found_spec != specialisations.end();
    }

    void ability_group::add_ability(ability new_ability)
    {
      if (!can_manage_ability(new_ability.name()))
        throw exception::invalid_parameter();

      if (has_ability(new_ability.name()))
        set_ability_value(new_ability.name(), new_ability.get_ability_value());
      else
        actual_abilities.push_back(new_ability);
    }

    void ability_group::add_ability(const std::string& new_ability_name, unsigned int new_ability_value)
    {
      add_ability(ability(new_ability_name, new_ability_value));
    }

    void ability_group::set_ability_value(const std::string& ability_name, unsigned int new_value)
    {
      if (!has_ability(ability_name))
        actual_abilities.emplace_back(ability(ability_name, new_value));

      get_ability_reference(ability_name)->set_value(new_value);
    }

    void ability_group::increase_ability_value(const std::string& ability_name, unsigned int add_value)
    {
      if (has_ability(ability_name))
        {
          set_ability_value(ability_name, get_ability(ability_name).get_ability_value() + add_value);
        }
    }

    std::vector<detailed_ability> ability_group::get_detailed_abilities() const
    {
      std::vector<detailed_ability> result;

      for (auto ability: actual_abilities)
        result.push_back(detailed_ability(macro_ability, ability.name()));

      return result;
    }

    void ability_group::set_favourite(bool is_favourite, const std::string &declination_name)
    {
      get_ability_reference(declination_name)->set_favourite(is_favourite);
    }

    void ability_group::add_specialisation(specialisation new_specialisation)
    {
      if (get_specialisation_reference(new_specialisation.name()) == specialisations.end())
        specialisations.push_back(new_specialisation);
      else
        get_specialisation_reference(new_specialisation.name())->set_value(new_specialisation.value());
    }

    void ability_group::add_specialisation(const std::string& new_specialisation_name, unsigned int initial_value)
    {
      add_specialisation(specialisation(new_specialisation_name, initial_value));
    }

    void ability_group::set_specialisation_value(const std::string& specialisation_name, unsigned int new_value)
    {
      if (!has_specialisation(specialisation_name))
        specialisations.emplace_back(specialisation(specialisation_name, new_value));

      get_specialisation_reference(specialisation_name)->set_value(new_value);
    }

    void ability_group::increase_specialisation_value(const std::string& specialisation_name, unsigned int add_value)
    {
      if (!has_specialisation(specialisation_name))
        throw exception::ability_not_found_exception();

      auto specialisation = get_specialisation_reference(specialisation_name);
      specialisation->set_value(specialisation->value() + add_value);
    }

    void ability_group::remove_specialisation(const std::string& specialisation_to_remove)
    {
      if (has_specialisation(specialisation_to_remove))
        specialisations.erase(get_specialisation_reference(specialisation_to_remove));
    }

    bool ability_group::has_abilities() const
    {
      return (actual_abilities.size() > 1)
          || (actual_abilities.begin()->name() != ability_declination::NO_DECLINATION);
    }

    bool ability_group::can_manage_ability(const std::string& ability_name) const
    {
      return has_abilities() || ability_name == ability_declination::NO_DECLINATION;
    }

    std::vector<ability>::iterator ability_group::get_ability_reference(const std::string &name)
    {
      return std::find_if(actual_abilities.begin(), actual_abilities.end(),
        [name] (ability ab)
        {
          return ab.name() == name;
        });
    }

    std::vector<specialisation>::iterator ability_group::get_specialisation_reference(const std::string &name)
    {
      return std::find_if(specialisations.begin(), specialisations.end(),
        [name] (specialisation spec)
        {
          return spec.name() == name;
        });
    }

    void ability_group::serialisation()
    {
      synch(serialisation::json_constants::SLOT_NAME     ,      macro_ability);
      synch(serialisation::json_constants::SLOT_ABILITIES,      actual_abilities);
      synch(serialisation::json_constants::SLOT_SPECIALISATIONS,specialisations);
    }
}

