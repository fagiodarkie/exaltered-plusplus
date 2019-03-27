#include "abilities/abilities.h"
#include "abilities/ability_names.h"

namespace character {
  void abilities::read(const QJsonObject& json)
  {
    clear();
    for (ability_name ability_type: ABILITY_NAME.keys())
      {
        QString ability_name = ABILITY_NAME[ability_type];
        int ability_value = json[ability_name].toInt();
        ability ability(ability_name, ability_value);
        insert(ability_type, ability);
      }
  }

  void abilities::write(QJsonObject &json) const
  {
    for (ability_name ability_type: ABILITY_NAME.keys())
      {
        QString ability_name = ABILITY_NAME[ability_type];
        int ability_value = int(value(ability_type));
        json[ability_name] = ability_value;
      }
  }
}
