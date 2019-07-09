#pragma once

#include "serialisable.h"

namespace character {
  namespace power {
    class willpower : public serialisable
    {
    public:
      willpower(unsigned int total = 0, unsigned int temporary = 0);

      unsigned int temporary_willpower() const;
      bool can_consume(unsigned int to_consume = 1) const;
      void consume(unsigned int to_consume = 1);
      void restore(unsigned int to_restore = 1);

      unsigned int permanent_willpower() const;
      void set_permanent_willpower(unsigned int permanent_willpower);

      void read_from_json(const QJsonObject &json);
      void write_to_json(QJsonObject &json) const;

      virtual ~willpower();

    private:
      unsigned int _permanent_willpower, _temporary_willpower;
    };
  }
}

