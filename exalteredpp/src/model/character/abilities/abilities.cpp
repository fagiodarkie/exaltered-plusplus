#include "abilities/abilities.h"
#include "abilities/ability_names.h"

namespace character {
  void abilities::read_from_json(const QJsonObject& json)
  {
    clear();
    for (ability_name ability_type: ABILITY_NAME.keys())
      {
        QString ability_name = ABILITY_NAME[ability_type];
        ability_group ability_gr(ability_name);
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
