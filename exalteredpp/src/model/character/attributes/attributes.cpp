#include "attributes/attributes.h"

namespace character {
  void attributes::read(const QJsonObject& json)
  {
    clear();
    for (attribute_name attribute_type: ATTRIBUTE_NAME.keys())
      {
        QString attribute_name = ATTRIBUTE_NAME[attribute_type];
        int attribute_value = json[attribute_name].toInt();
        attribute attribute(attribute_name, attribute_value);
        emplace(attribute_type, attribute);
      }
  }

  void attributes::write(QJsonObject &json) const
  {
    for (attribute_name attribute_type: ATTRIBUTE_NAME.keys())
      {
        QString attribute_name = ATTRIBUTE_NAME[attribute_type];
        int attribute_value = int(at(attribute_type));
        json[attribute_name] = attribute_value;
      }
  }
}
