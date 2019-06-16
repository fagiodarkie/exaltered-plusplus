#pragma once

#include "virtue_names.h"
#include "serialisable.h"

namespace character {
  namespace virtues {
    class virtue : public serialisable
    {
    public:
      virtue(QJsonObject object);
      virtue(virtue_enum virtue_e, unsigned int value, virtue_rank rank);

      virtue_enum virtue_enum() const;

      virtue_rank rank() const;

      unsigned int value() const;
      void set_value(unsigned int value);

    private:
      enum virtue_enum _virtue_enum;
      virtue_rank _rank;
      unsigned int _value;

      // serialisable interface
    public:
      void read_from_json(const QJsonObject &json);
      void write_to_json(QJsonObject &json) const;

      virtual ~virtue();
    };
  }
}
