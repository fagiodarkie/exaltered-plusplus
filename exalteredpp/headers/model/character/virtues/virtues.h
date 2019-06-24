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

      virtual ~virtues();
    };
  }
}

