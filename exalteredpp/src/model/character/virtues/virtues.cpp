#include "virtues/virtues.h"
#include "virtues/virtue_names.h"

#include "invalid_parameter.h"
#include "json_constants.h"

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

      json[serialisation::json_constants::SLOT_VICE_ID] = QString::number(_vice);
      json[serialisation::json_constants::SLOT_VICE_VALUE] = QString::number(_vice_value);
    }

    void virtues::read_from_json(const QJsonObject &json)
    {
      for (virtue_enum virtue_e : VIRTUE_LIST)
        {
          QJsonObject inner_json = json[VIRTUE_NAME.value(virtue_e)].toObject();
          virtue v = virtue(inner_json);
          insert(virtue_e, v);
        }

      _vice = vice_enum(json[serialisation::json_constants::SLOT_VICE_ID].toInt());
      _vice_value = static_cast<unsigned int>(json[serialisation::json_constants::SLOT_VICE_VALUE].toInt());
    }

    virtue virtues::value(virtue_enum virtue_name) const
    {
      auto found_virtue = std::find_if(begin(), end(), [virtue_name](virtue cur_virtue) -> bool {
          return cur_virtue.virtue_enum() == virtue_name;
        });
      if (found_virtue != end())
        {
          return *found_virtue;
        }

      throw new exception::invalid_parameter();
    }

    void virtues::set_vice(vice_enum vice_name, unsigned int vice_value)
    {
      _vice = vice_name;
      _vice_value = vice_value;
    }

    vice_enum virtues::vice() const
    {
      return _vice;
    }

    unsigned int virtues::vice_value() const
    {
      return _vice_value;
    }

    virtues::~virtues() {}
  }
}
