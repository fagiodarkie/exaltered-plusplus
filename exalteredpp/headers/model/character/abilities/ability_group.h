#pragma once

#include "ability.h"
#include "ability_names.h"
#include "specialisation.h"
#include "../thirdparty/serialisable/serialisable.hpp"

namespace character
{
  class ability_group : public Serialisable
  {
  public:

    ability_group(ability_names::ability_enum ability_e = ability_names::WAR,
                  std::vector<ability> abilities = { ability(ability_names::ability_declination::NO_DECLINATION) },
                  std::vector<specialisation> specialisations = {});
    ability_group(const ability_group& o);
    ability_group& operator=(const ability_group& o);

    ability_names::ability_enum get_ability_enum() const;
    std::string get_name() const;
    ability get_ability(const std::string& name = ability_names::ability_declination::NO_DECLINATION) const;
    specialisation get_specialisation(const std::string& name) const;
    ability_names::ability_category get_category() const;

    std::vector<ability> get_abilities() const;
    std::vector<specialisation> get_specialisations() const;

    bool has_ability(const std::string& ability_name) const;
    bool has_specialisation(const std::string& specialisation_name) const;

    void add_ability(ability new_ability);
    void add_ability(const std::string& new_ability_name, unsigned int new_ability_value = 0);
    void set_ability_value(const std::string& ability_name, unsigned int new_value);
    void increase_ability_value(const std::string& ability_name, unsigned int add_value = 1);
    void set_favourite(bool is_favourite, const std::string& declination_name = ability_names::ability_declination::NO_DECLINATION);

    void add_specialisation(specialisation new_specialisation);
    void add_specialisation(const std::string& new_specialisation_name, unsigned int initial_value = 1);
    void set_specialisation_value(const std::string& specialisation_name, unsigned int new_value);
    void increase_specialisation_value(const std::string& specialisation_name, unsigned int add_value = 1);
    void remove_specialisation(const std::string& specialisation_to_remove);

    bool has_abilities() const;

    virtual void serialisation() override;

    virtual ~ability_group() = default;

  private:
    ability_names::ability_enum macro_ability;
    std::vector<ability> actual_abilities;
    std::vector<specialisation> specialisations;
    bool is_favorite;

    bool can_manage_ability(const std::string& ability_name) const;
    std::vector<ability>::iterator get_ability_reference(const std::string& name);
    std::vector<specialisation>::iterator get_specialisation_reference(const std::string& name);

  };
}

