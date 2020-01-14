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

    void virtues::serialisation()
    {
      for (virtue_enum virtue_e : VIRTUE_LIST)
        {
          synch(VIRTUE_NAME.at(virtue_e), operator[](virtue_e));
        }

      synch(serialisation::json_constants::SLOT_VICE_ID, _vice);
      synch(serialisation::json_constants::SLOT_VICE_VALUE, _vice_value);
    }

    virtue& virtues::value(virtue_enum virtue_name)
    {
      return *std::find_if(begin(), end(), [virtue_name](virtue cur_virtue) -> bool {
          return cur_virtue.virtue_type() == virtue_name;
        });
    }

    virtue& virtues::operator[](int index)
    {
      virtue_enum virtue_name = static_cast<virtue_enum>(index);
      return value(virtue_name);
    }

    virtue virtues::value(virtue_enum virtue_name) const
    {
      return *std::find_if(begin(), end(), [virtue_name](virtue cur_virtue) -> bool {
          return cur_virtue.virtue_type() == virtue_name;
        });
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
      return static_cast<vice_enum>(_vice);
    }

    unsigned int virtues::vice_value() const
    {
      return _vice_value;
    }

    virtues::~virtues() {}
  }
}
