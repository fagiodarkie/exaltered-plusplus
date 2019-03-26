#include "abilities/abilities.h"

namespace character {
  void abilities::read(const QJsonObject& json)
  {
    clear();
    for (ability_name attribute_type: ATTRIBUTE_NAME.keys())
      {
        QString ability_name = ATTRIBUTE_NAME[attribute_type];
        int ability_value = json[ability_name].toInt();
        ability ability(ability_name, ability_value);
        insert(attribute_type, ability);
      }
  }

  void abilities::write(QJsonObject &json) const
  {
    for (ability_name attribute_type: ATTRIBUTE_NAME.keys())
      {
        QString attribute_name = ATTRIBUTE_NAME[attribute_type];
        int attribute_value = int(value(attribute_type));
        json[attribute_name] = attribute_value;
      }
  }
}
