#pragma once

#include "abstract_calculator_worker.h"
#include "rounding_type.h"

namespace calculator {
  namespace worker {

    template <typename round_t>
    class common_worker : public abstract_calculator_worker
    {
    public:
      virtual long int compute_dodge_dv(const character::character& c) const override
      {
        return round<round_t>(_dodge_dv(c));
      }

      virtual long int compute_parry_dv(const character::character& c, character::ability_names::ability_enum parry_ability) const override
      {
        return round<round_t>(_parry_dv(c, parry_ability));
      }

      virtual long int compute_heavy_parry_dv(const character::character& c, character::ability_names::ability_enum parry_ability) const override
      {
        return round<round_t>(_heavy_parry_dv(c, parry_ability));
      }

      virtual long int compute_mental_dodge_dv(const character::character& c) const override
      {
        return round<round_t>(_mental_dodge_dv(c));
      }

      virtual long int compute_mental_parry_dv(const character::character& c, character::attribute_names::attribute parry_attribute) const override
      {
        return round<round_t>(_mental_parry_dv(c, parry_attribute));
      }

      virtual long int compute_persona(const character::character& c) const override
      {
        return round<round_t>(_persona(c));
      }

      virtual ~common_worker() override {}

    protected:
      template<typename round_t>
      // round_t must implement a static unsigned long int round(const double) method.
      typename std::enable_if<
        std::is_constructible<long int,
        decltype(round_t::round(std::declval<const double>()))
      >::value, long int>::type
      round(const double value) const
      {
        return round_t::round(value);
      }

    private:

      typedef character::attribute_names::attribute attribute_t;
      typedef character::ability_names::ability_enum ability_t;

      virtual double _dodge_dv(const character::character& c) const
      {
        return half(c, attribute_t::DEXTERITY, ability_t::DODGE);
      }

      // TODO parry computations must take into account weapon DV!
      virtual double _parry_dv(const character::character& c, character::ability_names::ability_enum parry_ability) const
      {
        return half(c, attribute_t::STRENGTH, attribute_t::DEXTERITY) + c.get_ability(parry_ability) / 2;
      }

      virtual double _heavy_parry_dv(const character::character& c, character::ability_names::ability_enum parry_ability) const
      {
        ability_t actual_ability = c.get_ability(ability_t::RESISTANCE) >= c.get_ability(parry_ability) ? parry_ability : ability_t::RESISTANCE;
        return half(c, attribute_t::STRENGTH, actual_ability);
      }

      virtual double _mental_dodge_dv(const character::character& c) const
      {
        return half(c, attribute_t::WITS, ability_t::INTEGRITY);
      }

      virtual double _mental_parry_dv(const character::character& c, character::attribute_names::attribute parry_attribute) const
      {
        return half(c, attribute_t::INTELLIGENCE, parry_attribute);
      }

      virtual double _persona(const character::character& c) const
      {
        unsigned int persona = c.get_willpower().permanent_willpower();

        for (auto social_attribute : character::attribute_names::ATTRIBUTES_BY_CATEGORY.at(character::attribute_names::SOCIAL))
          persona += c.get_attribute(social_attribute);

        return static_cast<double>(persona);
      }

      virtual double half(const character::character& c, attribute_t attribute, ability_t ability) const
      {
        return static_cast<double>(c.get_attribute(attribute) + c.get_ability(ability)) / 2;
      }

      virtual double half(const character::character& c, ability_t ability, attribute_t attribute) const
      {
        return half(c, attribute, ability);
      }

      virtual double half(const character::character& c, attribute_t attribute, attribute_t attribute_2) const
      {
        return static_cast<double>(c.get_attribute(attribute) + c.get_attribute(attribute_2)) / 2;
      }
    };

    class human_worker : public common_worker<round_down>
    {
      virtual ~human_worker() {}
    };

  }
}
