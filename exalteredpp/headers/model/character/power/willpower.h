#pragma once

#include "serialisable.h"

namespace character {
  namespace power {
    class willpower : public serialisable
    {
    public:
      willpower();

      unsigned int temporary_willpower() const;

      unsigned int permanent_willpower() const;

      void read_from_json(const QJsonObject &json);
      void write_to_json(QJsonObject &json) const;

      virtual ~willpower();

    private:
      unsigned int _permanent_willpower, _temporary_willpower;
    };
  }
}

