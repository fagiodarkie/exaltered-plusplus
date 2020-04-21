#include "equipment/craft/material.h"

#include "serialisation/json_constants.h"

namespace equipment {
  namespace craft {

    material::material()
        : _category(material_category::METAL),
        _subcategory(submaterial_category::COMMON_METAL),
        _hardness(hardness::HARD),
        _craft_resistance(0), _cost(0), _availability(0), _tenaciousness(0), _break_point(0), _slots_taken(1), _minimum(0),
        _defense_bonus(0), _precision_bonus(0), _drill_bonus(0), _im_bonus(0), _changes_damage_type(false), _overridden_damage_type(combat::damage_type_enum::BASHING)
    {
        for (auto damage: combat::DAMAGES)
        {
            _soak[damage] = 0;
            _damage_bonus[damage] = 0;
        }

    };

    void material::serialisation()
    {
      synch(serialisation::json_constants::SLOT_CRAFT_MATERIAL_CATEGORY              , _category);
      synch(serialisation::json_constants::SLOT_CRAFT_MATERIAL_SUBCATEGORY           , _subcategory);
      synch(serialisation::json_constants::SLOT_CRAFT_MATERIAL_HARDNESS              , _hardness);
      synch(serialisation::json_constants::SLOT_CRAFT_MATERIAL_CRAFT_RESISTANCE      , _craft_resistance);
      synch(serialisation::json_constants::SLOT_CRAFT_MATERIAL_COST                  , _cost);
      synch(serialisation::json_constants::SLOT_CRAFT_MATERIAL_AVAILABILITY          , _availability);
      synch(serialisation::json_constants::SLOT_CRAFT_MATERIAL_TENACIOUSNESS         , _tenaciousness);
      synch(serialisation::json_constants::SLOT_CRAFT_MATERIAL_BREAKPOINT            , _break_point);
      synch(serialisation::json_constants::SLOT_CRAFT_MATERIAL_SLOTS                 , _slots_taken);
      synch(serialisation::json_constants::SLOT_CRAFT_MATERIAL_MIN_DAMAGE            , _minimum);
      synch(serialisation::json_constants::SLOT_CRAFT_MATERIAL_DEFENSE_BONUS         , _defense_bonus);
      synch(serialisation::json_constants::SLOT_CRAFT_MATERIAL_PRECISION_BONUS       , _precision_bonus);
      synch(serialisation::json_constants::SLOT_CRAFT_MATERIAL_DRILL_BONUS           , _drill_bonus);
      synch(serialisation::json_constants::SLOT_CRAFT_MATERIAL_IM_BONUS              , _im_bonus);
      synch(serialisation::json_constants::SLOT_CRAFT_MATERIAL_CHANGES_DAMAGE_TYPE   , _changes_damage_type);
      synch(serialisation::json_constants::SLOT_CRAFT_MATERIAL_OVERRIDDEN_DAMAGE_TYPE, _overridden_damage_type);

      synch(serialisation::json_constants::SLOT_NAME, _name);
    }
    
    material_category material::category() const
    {
        return _category;
    }
    
    void material::set_category(const material_category &category)
    {
        _category = category;
    }
    
    submaterial_category material::subcategory() const
    {
        return _subcategory;
    }
    
    void material::set_subcategory(const submaterial_category &subcategory)
    {
        _subcategory = subcategory;
    }
    
    enum hardness material::hardness() const
    {
        return _hardness;
    }
    
    void material::set_hardness(const enum hardness &hardness)
    {
        _hardness = hardness;
    }
    
    std::string material::name() const
    {
        return _name;
    }
    
    void material::set_name(const std::string &name)
    {
        _name = name;
    }
    
    unsigned short material::craft_resistance() const
    {
        return _craft_resistance;
    }
    
    void material::set_craft_resistance(unsigned short craft_resistance)
    {
        _craft_resistance = craft_resistance;
    }
    
    unsigned short material::cost() const
    {
        return _cost;
    }
    
    void material::set_cost(unsigned short cost)
    {
        _cost = cost;
    }

    unsigned short material::availability() const
    {
        return _availability;
    }

    void material::set_availability(unsigned short availability)
    {
        _availability = availability;
    }

    unsigned short material::tenaciousness() const
    {
        return _tenaciousness;
    }

    void material::set_tenaciousness(unsigned short tenaciousness)
    {
        _tenaciousness = tenaciousness;
    }

    unsigned short material::break_point() const
    {
        return _break_point;
    }

    void material::set_break_point(unsigned short break_point)
    {
        _break_point = break_point;
    }

    unsigned short material::slots_taken() const
    {
        return _slots_taken;
    }

    void material::set_slots_taken(unsigned short slots_taken)
    {
        _slots_taken = slots_taken;
    }

    unsigned short material::minimum() const
    {
        return _minimum;
    }

    void material::set_minimum(unsigned short minimum)
    {
        _minimum = minimum;
    }

    bool material::changes_damage_type() const
    {
        return _changes_damage_type;
    }

    void material::set_changes_damage_type(bool changes_damage_type)
    {
        _changes_damage_type = changes_damage_type;
    }

    combat::damage_type_enum material::overridden_damage_type() const
    {
        return _overridden_damage_type;
    }

    void material::set_overridden_damage_type(const combat::damage_type_enum &overridden_damage_type)
    {
        _overridden_damage_type = overridden_damage_type;
    }
    
    short material::defense_bonus() const
    {
        return _defense_bonus;
    }
    
    void material::set_defense_bonus(short defense_bonus)
    {
        _defense_bonus = defense_bonus;
    }
    
    short material::precision_bonus() const
    {
        return _precision_bonus;
    }
    
    void material::set_precision_bonus(short precision_bonus)
    {
        _precision_bonus = precision_bonus;
    }
    
    short material::drill_bonus() const
    {
        return _drill_bonus;
    }
    
    void material::set_drill_bonus(short drill_bonus)
    {
        _drill_bonus = drill_bonus;
    }
    
    short material::im_bonus() const
    {
        return _im_bonus;
    }
    
    void material::set_im_bonus(short im_bonus)
    {
        _im_bonus = im_bonus;
    }

    void material::with_soak(combat::damage_type_enum damage, short int soak)
    {
      _soak[damage] = soak;
    }

    short int material::soak(combat::damage_type_enum damage) const
    {
      return _soak.at(damage);
    }

    void material::with_damage_bonus(combat::damage_type_enum damage, short int d_bonus)
    {
      _damage_bonus[damage] = d_bonus;
    }

    short int material::damage_bonus(combat::damage_type_enum damage) const
    {
      return _damage_bonus.at(damage);
    }
  }
}
