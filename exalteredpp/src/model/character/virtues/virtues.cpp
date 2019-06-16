#include "virtues/virtues.h"
#include "virtues/virtue_names.h"

namespace character {
  namespace virtues {
    void virtues::write_to_json(QJsonObject &json) const
    {
      for (virtue_enum virtue_e : VIRTUE_LIST)
        {
          QJsonObject inner_json;
          value(virtue_e).write_to_json(inner_json);
          json[VIRTUE_NAME.value(virtue_e)] = inner_json;
        }
    }

    void virtues::read_from_json(const QJsonObject &json)
    {
      for (virtue_enum virtue_e : VIRTUE_LIST)
        {
          QJsonObject inner_json = json[VIRTUE_NAME.value(virtue_e)].toObject();
          virtue v = virtue(inner_json);
          insert(virtue_e, v);
        }
    }
  }
}
