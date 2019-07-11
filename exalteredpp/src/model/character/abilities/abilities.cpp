#include "abilities/abilities.h"
#include "abilities/ability_names.h"

namespace character {
  void abilities::read_from_json(const QJsonObject& json)
  {
    clear();
    for (ability_names::ability_enum ability_type: ability_names::ABILITY_NAME.keys())
      {
        QString ability_name = ability_names::ABILITY_NAME[ability_type];

        ability_names::ability_category category = ability_names::SOCIAL;
        for (auto category_it : ability_names::ABILITIES_IN_CATEGORY.keys())
          if (ability_names::ABILITIES_IN_CATEGORY[category_it].contains(ability_type))
            category = category_it;

        ability_group ability_gr(ability_name, category);
        ability_gr.read_from_json(json[ability_name].toObject());
        insert(ability_type, ability_gr);
      }
  }

  void abilities::write_to_json(QJsonObject &json) const
  {
    for (ability_group ability: values())
      {
        QJsonObject ability_object;
        ability.write_to_json(ability_object);
        json[ability.get_name()] = ability_object;
      }
  }
}
