#pragma once

#include "serialisable.h"

namespace character {
  namespace social {

    class philosophy : public serialisable
    {
    public:
      philosophy(QString name = "", unsigned int value = 1);

      QString name() const;
      unsigned int value() const;

      void set_value(unsigned int new_value);

      bool operator== (const philosophy& o) const;

      void read_from_json(const QJsonObject &json);
      void write_to_json(QJsonObject &json) const;

      virtual ~philosophy();

    private:
      unsigned int _value;
      QString _name;
    };
  }
}
