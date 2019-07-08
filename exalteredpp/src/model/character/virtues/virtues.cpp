#include "virtues/virtues.h"
#include "virtues/virtue_names.h"

#include "invalid_parameter.h"
#include "json_constants.h"

namespace character {
  namespace virtues {

    virtues::virtues()
      : _vice(LUST), _vice_value(1)
    {
      for (virtue_enum virtue_e: VIRTUE_LIST)
        {
          push_back(virtue(virtue_e, 1, ADULT));
        }
    }

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
          if (json[VIRTUE_NAME.value(virtue_e)].isUndefined())
            continue;

          QJsonObject inner_json = json[VIRTUE_NAME.value(virtue_e)].toObject();
          virtue v = virtue(inner_json);
          insert(virtue_e, v);
        }

      _vice = json[serialisation::json_constants::SLOT_VICE_ID].isUndefined() ? LUST : vice_enum(json[serialisation::json_constants::SLOT_VICE_ID].toInt());
      _vice_value = json[serialisation::json_constants::SLOT_VICE_VALUE].isUndefined() ? 1 : static_cast<unsigned int>(json[serialisation::json_constants::SLOT_VICE_VALUE].toString().toInt());
    }

    virtue& virtues::value(virtue_enum virtue_name)
    {
      auto found_virtue = std::find_if(begin(), end(), [virtue_name](virtue cur_virtue) -> bool {
          return cur_virtue.virtue_type() == virtue_name;
        });
      if (found_virtue != end())
        {
          return *found_virtue;
        }

      throw new exception::invalid_parameter();
    }

    virtue& virtues::operator[](int index)
    {
      virtue_enum virtue_name = static_cast<virtue_enum>(index);
      return value(virtue_name);
    }

    virtue virtues::value(virtue_enum virtue_name) const
    {
      auto found_virtue = std::find_if(begin(), end(), [virtue_name](virtue cur_virtue) -> bool {
          return cur_virtue.virtue_type() == virtue_name;
        });
      if (found_virtue != end())
        {
          return *found_virtue;
        }

      throw new exception::invalid_parameter();
    }

    virtue virtues::operator[](int index) const
    {
      virtue_enum virtue_name = static_cast<virtue_enum>(index);
      return value(virtue_name);
    }

    void virtues::set_vice_type(vice_enum vice_name)
    {
      _vice = vice_name;
    }

    void virtues::set_vice_value(unsigned int value)
    {
      _vice_value = value;
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
