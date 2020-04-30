#ifndef ATTACK_STAT_H
#define ATTACK_STAT_H

#include "craft_defines.h"
#include "../thirdparty/serialisable/serialisable.hpp"
#include "combat/attack_defines.h"
#include "attributes/attribute_names.h"

namespace equipment {
  namespace craft {

    using combat::damage_type_enum;
    using combat::attack_attribute;

    class attack_stat : public Serialisable
    {
    public:

      attack_stat();
      attack_stat(int im, int precision, int damage, int range, int cadence, int min_damage, int drill,
                  damage_type_enum damage_type,
                  attribute::attribute_enum precision_attribute, attribute::attribute_enum damage_attribute);

      attack_stat(const attack_stat& o);

      static const attack_stat IMPROVISED_BASH, IMPROVISED_SLASH, IMPROVISED_THROW, IMPROVISED_GRAPPLE;

      int _im, _precision, _damage, _range, _cadence, _minimum_damage, _drill;
      damage_type_enum _damage_type;
      attribute::attribute_enum _precision_attribute, _damage_attribute;
      std::vector<note> _notes;

      void serialisation() override;
    };
  }
}

#endif // ATTACK_STAT_H
