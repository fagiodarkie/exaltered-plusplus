#include "abilities/ability_group.h"
#include "ability_not_found_exception.h"
#include "invalid_parameter.h"
#include "json_constants.h"

#include <QJsonArray>
#include <algorithm>

namespace character
{
    ability_group::ability_group(const QString& name, ability_names::ability_category category, QList<ability> abilities, QList<specialisation> existing_specialisations)
      : group_name(name), category(category), actual_abilities(abilities), specialisations(existing_specialisations)
    { }

    QString ability_group::get_name() const
    {
      return group_name;
    }

    QList<ability> ability_group::get_abilities() const
    {
      if (!has_abilities())
        return { ability(group_name, get_ability().get_ability_value()) };

      QList<ability> mod_abilities;
      for (ability a : actual_abilities)
        {
          mod_abilities.push_back(ability(QString("%1 (%2)").arg(group_name).arg(a.get_name()), a.get_ability_value()));
        }

      return mod_abilities;
    }

    QList<specialisation> ability_group::get_specialisations() const
    {
      return specialisations;
    }

    ability_names::ability_category ability_group::get_category() const
    {
      return category;
    }

    ability ability_group::get_ability(const QString& name) const
    {
      for (ability ab : actual_abilities)
        {
          if (ab.get_name() == name)
            return ab;
        }
      throw exception::ability_not_found_exception();
    }

    specialisation ability_group::get_specialisation(const QString& name) const
    {
      for (specialisation spec : specialisations)
        {
          if (spec.get_name() == name)
            return spec;
        }
      throw exception::ability_not_found_exception();
    }

    bool ability_group::has_ability(const QString& ability_name) const
    {      
      auto found_ability = std::find_if(actual_abilities.begin(), actual_abilities.end(),
        [ability_name] (ability ab)
        {
          return ab.get_name() == ability_name;
        });

      return found_ability != actual_abilities.end();
    }

    bool ability_group::has_specialisation(const QString& specialisation_name) const
    {
      auto found_spec = std::find_if(specialisations.begin(), specialisations.end(),
         [specialisation_name] (specialisation spec)
         {
           return spec.get_name() == specialisation_name;
         });

      return found_spec != specialisations.end();
    }

    void ability_group::add_ability(ability new_ability)
    {
      if (!can_manage_ability(new_ability.get_name()))
        throw exception::invalid_parameter();

      if (has_ability(new_ability.get_name()))
        set_ability_value(new_ability.get_name(), new_ability.get_ability_value());
      else
        actual_abilities.push_back(new_ability);
    }

    void ability_group::add_ability(const QString& new_ability_name, unsigned int new_ability_value)
    {
      add_ability(ability(new_ability_name, new_ability_value));
    }

    void ability_group::set_ability_value(const QString& ability_name, unsigned int new_value)
    {
      if (!has_ability(ability_name))
        throw exception::ability_not_found_exception();

      get_ability_reference(ability_name)->set_value(new_value);
    }

    void ability_group::increase_ability_value(const QString& ability_name, unsigned int add_value)
    {
      if (has_ability(ability_name))
        {
          set_ability_value(ability_name, get_ability(ability_name).get_ability_value() + add_value);
        }
    }

    void ability_group::add_specialisation(specialisation new_specialisation)
    {
      if (get_specialisation_reference(new_specialisation.get_name()) == specialisations.end())
        specialisations.push_back(new_specialisation);
    }

    void ability_group::add_specialisation(const QString& new_specialisation_name, unsigned int initial_value)
    {
      add_specialisation(specialisation(new_specialisation_name, initial_value));
    }

    void ability_group::set_specialisation_value(const QString& specialisation_name, unsigned int new_value)
    {
      if (!has_specialisation(specialisation_name))
        throw exception::ability_not_found_exception();

      get_specialisation_reference(specialisation_name)->set_value(new_value);
    }

    void ability_group::increase_specialisation_value(const QString& specialisation_name, unsigned int add_value)
    {
      if (!has_specialisation(specialisation_name))
        throw exception::ability_not_found_exception();

      auto specialisation = get_specialisation_reference(specialisation_name);
      specialisation->set_value(specialisation->get_specialisation_value() + add_value);
    }

    void ability_group::remove_specialisation(const QString& specialisation_to_remove)
    {
      if (has_specialisation(specialisation_to_remove))
        specialisations.removeAll(*get_specialisation_reference(specialisation_to_remove));
    }

    bool ability_group::has_abilities() const
    {
      return (actual_abilities.count() > 1)
          || (actual_abilities.at(0).get_name() != ability_names::ability_declination::NO_DECLINATION);
    }

    bool ability_group::can_manage_ability(const QString& ability_name) const
    {
      return has_abilities() || ability_name == ability_names::ability_declination::NO_DECLINATION;
    }

    QList<ability>::iterator ability_group::get_ability_reference(const QString &name)
    {
      return std::find_if(actual_abilities.begin(), actual_abilities.end(),
        [name] (ability ab)
        {
          return ab.get_name() == name;
        });
    }

    QList<specialisation>::iterator ability_group::get_specialisation_reference(const QString &name)
    {
      return std::find_if(specialisations.begin(), specialisations.end(),
        [name] (specialisation spec)
        {
          return spec.get_name() == name;
        });
    }

    bool ability_group::is_favourite() const
    {
      return is_favorite;
    }

    void ability_group::set_favourite(bool is_favourite)
    {
      is_favorite = is_favourite;
    }

    void ability_group::read_from_json(const QJsonObject &json)
    {
      group_name = json[serialisation::json_constants::SLOT_NAME].toString();
      actual_abilities.clear();
      specialisations.clear();

      is_favorite = json[serialisation::json_constants::SLOT_FAVOURITE].toBool();

      for (auto ability_obj: json[serialisation::json_constants::SLOT_ABILITIES].toArray())
        {
          ability ability;
          ability.read_from_json(ability_obj.toObject());
          actual_abilities.push_back(ability);
        }

      for (auto specialisation_obj: json[serialisation::json_constants::SLOT_SPECIALISATIONS].toArray())
        {
          specialisation spec("");
          spec.read_from_json(specialisation_obj.toObject());
          specialisations.push_back(spec);
        }
    }

    void ability_group::write_to_json(QJsonObject &json) const
    {
      json[serialisation::json_constants::SLOT_NAME] = group_name;
      QJsonArray abilities_array, specialisations_array;
      for (ability ab: actual_abilities)
        {
          QJsonObject ability_obj;
          ab.write_to_json(ability_obj);
          abilities_array.push_back(ability_obj);
        }

      for (specialisation spec: specialisations)
        {
          QJsonObject spec_obj;
          spec.write_to_json(spec_obj);
          specialisations_array.push_back(spec_obj);
        }

      json[serialisation::json_constants::SLOT_FAVOURITE] = is_favorite;
      json[serialisation::json_constants::SLOT_ABILITIES] = abilities_array;
      json[serialisation::json_constants::SLOT_SPECIALISATIONS] = specialisations_array;
    }
}

