#include "attributes/attributes.h"

namespace character {
  using namespace attribute_names;

  void attributes::read_from_json(const QJsonObject& json)
  {
    clear();
    for (auto attribute_type: ATTRIBUTE_NAME.keys())
      {
        QString attribute_name = ATTRIBUTE_NAME[attribute_type];
        int attribute_value = json[attribute_name].toInt();
        character::attribute computed_attribute(attribute_name, attribute_value);
        insert(attribute_type, computed_attribute);
      }
  }

  void attributes::write_to_json(QJsonObject &json) const
  {
    for (auto attribute_type: ATTRIBUTE_NAME.keys())
      {
        QString attribute_name = ATTRIBUTE_NAME[attribute_type];
        int attribute_value = int(value(attribute_type));
        json[attribute_name] = attribute_value;
      }
  }
}
