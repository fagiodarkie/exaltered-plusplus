#pragma once

#include "virtues/virtue.h"
#include "serialisation/serialisable.h"

namespace character {
  namespace virtues {
    class virtues : public QList<virtue>, public serialisable
    {
    public:
      void read_from_json(const QJsonObject &json);
      void write_to_json(QJsonObject &json) const;

      virtue value(virtue_enum virtue_name) const;

      void set_vice(vice_enum vice_name, unsigned int vice_value = 1);

      vice_enum vice() const;
      unsigned int vice_value() const;

      virtual ~virtues();

    private:
      vice_enum _vice;
      unsigned int _vice_value;
    };
  }
}

