#pragma once

#include "abstract_calculator_worker.h"
#include "rounding_type.h"
#include <cmath>

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
        return _persona(c.get_type(), c.get_attributes(), c.get_willpower(), c.get_essence());
      }

      virtual long int compute_persona                  (const character::creation::character_type& type, const character::attributes& attributes, const character::power::willpower& willpower, const character::power::essence& essence) const override
      {
        return _persona(type, attributes, willpower, essence);
      }

      virtual long int compute_bashing_soak             (const character::character& c)  const override
      {
        return round<round_t>(_bashing_soak(c));
      }

      virtual long int compute_lethal_soak              (const character::character& c)  const override
      {
        return round<round_t>(_lethal_soak(c));
      }

      virtual long int compute_aggravated_soak          (const character::character& c)  const override
      {
        return round<round_t>(_aggravated_soak(c));
      }

      virtual long int compute_natural_bashing_soak     (const character::character& c)  const override
      {
        return round<round_t>(_natural_bashing_soak(c));
      }

      virtual long int compute_natural_lethal_soak      (const character::character& c)  const override
      {
        return round<round_t>(_natural_lethal_soak(c));
      }

      virtual long int compute_natural_aggravated_soak  (const character::character& c)  const override
      {
        return round<round_t>(_natural_aggravated_soak(c));
      }

      virtual long int compute_personal_essence         (const character::character& c)  const override
      {
        return round<round_t>(_personal_essence(c));
      }

      virtual long int compute_peripheral_essence       (const character::character& c)  const override
      {
        return round<round_t>(_peripheral_essence(c));
      }

      virtual long int compute_spiritual_essence        (const character::character& c)  const override
      {
        return round<round_t>(_spiritual_essence(c));
      }

      virtual long int compute_celestial_portion        (const character::character& c)  const override
      {
        return round<round_t>(_celestial_portion(c));
      }

      virtual unsigned int compute_life_points              (const character::character& c) const override
      {
        return 10 * c.get_logos().get_logos() + 2 * c.get_attribute(attribute_t::CONSTITUTION);
      }

      virtual unsigned int starting_willpower               (const character::character& c) const override
      {
        std::vector<unsigned int> virtue_values = { c.get_virtue(character::virtues::COMPASSION).value(),
                                                  c.get_virtue(character::virtues::CONVINCTION) .value(),
                                                  c.get_virtue(character::virtues::VALOR)       .value(),
                                                  c.get_virtue(character::virtues::TEMPERANCE)  .value()};

        std::sort(virtue_values.begin(), virtue_values.end());

        return virtue_values[2] + virtue_values[3];
      }
      virtual unsigned int starting_khan                  (const character::creation::character_type& c) const override
      {
        switch(c)
          {
          case character::creation::TYPE_SOLAR_EXALT:
          case character::creation::TYPE_ABYSSAL_EXALT:
          case character::creation::TYPE_INFERNAL_EXALT:
            return 2;
          case character::creation::TYPE_TERRESTRIAL_EXALT:
            return 1;
          case character::creation::TYPE_MORTAL_HERO:
          case character::creation::TYPE_MORTAL_EXTRA:
            return 0;
          }
      }

      virtual long int compute_hindrance                (const character::character& c) const  override
      {
        // TODO not supported
        return 0;
      }

      virtual long int compute_stance_bonus             (const character::character& c) const  override
      {
        // TODO not supported
        return 0;
      }

      virtual long int compute_parry_balance            (const character::character& c) const  override
      {
        return c.get_attribute(attribute_t::DEXTERITY) - compute_hindrance(c);
      }

      virtual long int compute_dodge_balance            (const character::character& c) const  override
      {
        return c.get_attribute(attribute_t::CONSTITUTION) + compute_stance_bonus(c);
      }

      virtual long int compute_resilience               (const character::character& c) const  override
      {
        return c.get_ability(ability_t::INTEGRITY) + c.get_willpower().temporary_willpower();
      }

      virtual unsigned int starting_essence                  (const character::creation::character_type& c) const override
      {
        switch(c)
          {
          case character::creation::TYPE_SOLAR_EXALT:
          case character::creation::TYPE_ABYSSAL_EXALT:
          case character::creation::TYPE_INFERNAL_EXALT:
          case character::creation::TYPE_TERRESTRIAL_EXALT:
            return 2;
          case character::creation::TYPE_MORTAL_HERO:
          case character::creation::TYPE_MORTAL_EXTRA:
            return 1;
          }
      }

      virtual unsigned int starting_logos                    (const character::creation::character_type& c) const override
      {
        switch(c)
          {
          case character::creation::TYPE_SOLAR_EXALT:
          case character::creation::TYPE_ABYSSAL_EXALT:
          case character::creation::TYPE_INFERNAL_EXALT:
            return 2;
          case character::creation::TYPE_TERRESTRIAL_EXALT:
          case character::creation::TYPE_MORTAL_HERO:
          case character::creation::TYPE_MORTAL_EXTRA:
            return 1;
          }
      }

      virtual ~common_worker() override {}

    protected:
      template<typename T>
      // round_t must implement a static unsigned long int round(const double) method.
      typename std::enable_if<
        std::is_constructible<long int,
        decltype(T::round(std::declval<const double>()))
      >::value, long int>::type
      round(const double value) const
      {
        return T::round(value);
      }

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

      virtual long int _persona                  (const character::creation::character_type& type, const character::attributes& attributes, const character::power::willpower& willpower, const character::power::essence& ) const
      {
        unsigned int persona = willpower.permanent_willpower();

        for (auto social_attribute : character::attribute_names::ATTRIBUTES_BY_CATEGORY.at(character::attribute_names::SOCIAL))
          persona += attributes.at(social_attribute);

        return persona;
      }

      virtual double _bashing_soak             (const character::character& c) const
      {
        return c.get_attribute(attribute_t::CONSTITUTION);
      }

      virtual double _lethal_soak              (const character::character& c) const
      {
        return half(c, attribute_t::CONSTITUTION);
      }

      virtual double _aggravated_soak          (const character::character& c) const
      {
        return 0;
      }

      virtual double _natural_bashing_soak     (const character::character& c) const
      {
        return _bashing_soak(c);
      }

      virtual double _natural_lethal_soak      (const character::character& c) const
      {
        return _lethal_soak(c);
      }

      virtual double _natural_aggravated_soak  (const character::character& c) const
      {
        return _aggravated_soak(c);
      }

      virtual double _personal_essence         (const character::character& c) const
      {
        unsigned int permanent_essence = c.get_essence().permanent_essence();
        double exp = static_cast<double>(10 + permanent_essence) / 10;
        return (10 - permanent_essence) * std::pow(permanent_essence, exp);
      }

      virtual double _peripheral_essence       (const character::character& c) const {
        unsigned int permanent_essence = c.get_essence().permanent_essence();
        double exp = static_cast<double>(10 + permanent_essence) / 10;
        return std::pow(permanent_essence, exp) * c.get_essence().khan();
      }

      virtual double _spiritual_essence        (const character::character& c) const
      {
        double celestial_portion = _celestial_portion(c), terrestrial_portion = 1 - celestial_portion,
            peripheral = _peripheral_essence(c), personal = _personal_essence(c);

        return (celestial_portion * (peripheral + personal)) / terrestrial_portion;
      }

      virtual double _celestial_portion        (const character::character& c) const {
        switch(c.get_type())
          {
          case character::creation::TYPE_SOLAR_EXALT:
          case character::creation::TYPE_ABYSSAL_EXALT:
          case character::creation::TYPE_INFERNAL_EXALT:
          case character::creation::TYPE_TERRESTRIAL_EXALT:
            return 0.4 + 0.01 * c.get_essence().permanent_essence();
          case character::creation::TYPE_MORTAL_HERO:
          case character::creation::TYPE_MORTAL_EXTRA:
            return 0.3;
          }
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

      virtual double half(const character::character& c, attribute_t attribute) const
      {
        return static_cast<double>(c.get_attribute(attribute)) / 2;
      }
    };

    class human_worker : public common_worker<round_down>
    {
    public:
      virtual ~human_worker() {}
    };

  }
}
