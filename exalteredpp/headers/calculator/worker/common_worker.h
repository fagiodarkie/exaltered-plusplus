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

      virtual physical_defenses compute_physical_vd(const character::character& c, ability::ability_enum parry_ability) const override
      {
        physical_defenses result;

        result.dodge_vd         = compute_dodge_dv(c);
        result.parry_vd         = compute_parry_dv(c, parry_ability);
        result.tower_parry_vd   = compute_heavy_parry_dv(c, parry_ability);

        result.stance           = compute_stance_bonus(c);
        result.hindrance        = compute_hindrance(c);
        result.bashing_soak     = compute_bashing_soak(c);
        result.lethal_soak      = compute_lethal_soak(c);
        result.aggravated_soak  = compute_aggravated_soak(c);
        result.parry_balance    = compute_parry_balance(c);
        result.dodge_balance    = compute_dodge_balance(c);

        return result;
      }

      virtual mental_defenses compute_mental_vd(const character::character& c) const override
      {
        mental_defenses result;

        result.resilience = compute_resilience(c);
        result.mental_dodge_vd = compute_mental_dodge_dv(c);
        result.charisma_parry_vd = compute_mental_parry_dv(c, attribute::attribute_enum::CHARISMA);
        result.manipulation_parry_vd = compute_mental_parry_dv(c, attribute::attribute_enum::MANIPULATION);
        result.appearance_parry_vd = compute_mental_parry_dv(c, attribute::attribute_enum::APPEARANCE);

        return result;
      }

      virtual long int compute_dodge_dv(const character::character& c) const
      {
        auto result = _dodge_dv(c);
        return round<round_t>(result);
      }

      virtual long int compute_parry_dv(const character::character& c, ability::ability_enum parry_ability) const
      {
        auto parry = _parry_dv(c, parry_ability);
        return round<round_t>(parry);
      }

      virtual long int compute_heavy_parry_dv(const character::character& c, ability::ability_enum parry_ability) const
      {
        return round<round_t>(_heavy_parry_dv(c, parry_ability));
      }

      virtual long int compute_mental_dodge_dv(const character::character& c) const
      {
        return round<round_t>(_mental_dodge_dv(c));
      }

      virtual long int compute_mental_parry_dv(const character::character& c, attribute::attribute_enum parry_attribute) const
      {
        return round<round_t>(_mental_parry_dv(c, parry_attribute));
      }

      virtual long int compute_persona(const character::character& c) const override
      {
        return _persona(c.type(), c.attributes(), c.willpower(), c.essence());
      }

      virtual long int compute_persona                  (const character::creation::character_type& type, const attribute::attributes& attributes, const power::willpower& willpower, const power::essence& essence) const override
      {
        return _persona(type, attributes, willpower, essence);
      }

      virtual long int compute_bashing_soak             (const character::character& c)  const
      {
        return round<round_t>(_bashing_soak(c));
      }

      virtual long int compute_lethal_soak              (const character::character& c)  const
      {
        return round<round_t>(_lethal_soak(c));
      }

      virtual long int compute_aggravated_soak          (const character::character& c)  const
      {
        return round<round_t>(_aggravated_soak(c));
      }

      virtual long int compute_natural_bashing_soak     (const character::character& c)  const
      {
        return round<round_t>(_natural_bashing_soak(c));
      }

      virtual long int compute_natural_lethal_soak      (const character::character& c)  const
      {
        return round<round_t>(_natural_lethal_soak(c));
      }

      virtual long int compute_natural_aggravated_soak  (const character::character& c)  const
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
        return round<round_t>(_celestial_portion(c) * 100);
      }

      virtual unsigned int compute_life_points              (const character::character& c) const override
      {
        return 10 * c.logos().get_logos() + 2 * c.attribute(attribute::attribute_enum::CONSTITUTION);
      }

      virtual unsigned int starting_willpower               (const character::character& c) const override
      {
        std::vector<unsigned int> virtue_values = { c.virtue(virtues::COMPASSION).value(),
                                                    c.virtue(virtues::CONVINCTION) .value(),
                                                    c.virtue(virtues::VALOR)       .value(),
                                                    c.virtue(virtues::TEMPERANCE)  .value()};

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

      virtual long int compute_hindrance                (const character::character& c) const
      {
        // TODO not supported
        return 0;
      }

      virtual long int compute_stance_bonus             (const character::character& c) const
      {
        // TODO not supported
        return 0;
      }

      virtual long int compute_dodge_balance            (const character::character& c) const
      {
        return c.attribute(attribute::attribute_enum::DEXTERITY) - compute_hindrance(c);
      }

      virtual long int compute_parry_balance            (const character::character& c) const
      {
        return c.attribute(attribute::attribute_enum::CONSTITUTION) + compute_stance_bonus(c);
      }

      virtual long int compute_resilience               (const character::character& c) const
      {
        return round<round_t>(half(c, ability::ability_enum::INTEGRITY));
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

      virtual double _dodge_dv(const character::character& c) const
      {
        auto res = half(c, attribute::attribute_enum::DEXTERITY, ability::ability_enum::DODGE);
        return res;
      }

      // TODO parry computations must take into account weapon DV!
      virtual double _parry_dv(const character::character& c, ability::ability_enum parry_ability) const
      {
        auto att = half(c, attribute::attribute_enum::STRENGTH, attribute::attribute_enum::DEXTERITY);
        auto ab = c.get(parry_ability);
        return (ab + att) / 2;
      }

      virtual double _heavy_parry_dv(const character::character& c, ability::ability_enum parry_ability) const
      {
        ability::ability_enum actual_ability = c.get(parry_ability) < c.get(ability::ability_enum::RESISTANCE) ? parry_ability : ability::ability_enum::RESISTANCE;
        return half(c, attribute::attribute_enum::STRENGTH, actual_ability);
      }

      virtual double _mental_dodge_dv(const character::character& c) const
      {
        return half(c, attribute::attribute_enum::WITS, ability::ability_enum::INTEGRITY);
      }

      virtual double _mental_parry_dv(const character::character& c, attribute::attribute_enum parry_attribute) const
      {
        return half(c, attribute::attribute_enum::INTELLIGENCE, parry_attribute);
      }

      virtual long int _persona                  (const character::creation::character_type& type, const attribute::attributes& attributes, const power::willpower& willpower, const power::essence& ) const
      {
        unsigned int persona = willpower.permanent_willpower();

        for (auto social_attribute : attribute::ATTRIBUTES_BY_CATEGORY.at(attribute::SOCIAL))
          persona += attributes.at(social_attribute);

        return persona;
      }

      virtual double _bashing_soak             (const character::character& c) const
      {
        return c.attribute(attribute::attribute_enum::CONSTITUTION);
      }

      virtual double _lethal_soak              (const character::character& c) const
      {
        return 0;
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
        unsigned int permanent_essence = c.essence().permanent_essence();
        double exp = static_cast<double>(10 + permanent_essence) / 10;
        return (10 - permanent_essence) * std::pow(permanent_essence, exp);
      }

      virtual double _peripheral_essence       (const character::character& c) const {
        unsigned int permanent_essence = c.essence().permanent_essence();
        double exp = static_cast<double>(10 + permanent_essence) / 10;
        return std::pow(permanent_essence, exp) * c.essence().khan();
      }

      virtual double _spiritual_essence        (const character::character& c) const
      {
        double celestial_portion = _celestial_portion(c), terrestrial_portion = 1 - celestial_portion,
            peripheral = _peripheral_essence(c), personal = _personal_essence(c);

        return (celestial_portion * (peripheral + personal)) / terrestrial_portion;
      }

      virtual double _celestial_portion        (const character::character& c) const {
        switch(c.type())
          {
          case character::creation::TYPE_SOLAR_EXALT:
          case character::creation::TYPE_ABYSSAL_EXALT:
          case character::creation::TYPE_INFERNAL_EXALT:
          case character::creation::TYPE_TERRESTRIAL_EXALT:
            return 0.4 + 0.01 * c.essence().permanent_essence();
          case character::creation::TYPE_MORTAL_HERO:
          case character::creation::TYPE_MORTAL_EXTRA:
            return 0.3;
          }
        return 0;
      }

      virtual double half(const character::character& c, attribute::attribute_enum attribute, ability::ability_enum ability) const
      {
        return static_cast<double>(c.get(ability) + c.attribute(attribute)) / 2;
      }

      virtual double half(const character::character& c, ability::ability_enum ability, attribute::attribute_enum attribute) const
      {
        return half(c, attribute, ability);
      }

      virtual double half(const character::character& c, attribute::attribute_enum attribute, attribute::attribute_enum attribute_2) const
      {
        return static_cast<double>(c.attribute(attribute) + c.attribute(attribute_2)) / 2;
      }

      virtual double half(const character::character& c, attribute::attribute_enum attribute) const
      {
        return static_cast<double>(c.attribute(attribute)) / 2;
      }

      virtual double half(const character::character& c, ability::ability_enum ability) const
      {
        return static_cast<double>(c.get(ability)) / 2;
      }
    };

    class human_worker : public common_worker<round_down>
    {
    public:
      virtual ~human_worker() {}
    };

  }
}
