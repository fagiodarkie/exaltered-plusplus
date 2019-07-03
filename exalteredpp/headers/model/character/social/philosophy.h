#pragma once

#include "serialisable.h"

namespace character {
  namespace social {

    class philosophy : public serialisable
    {
    public:
      philosophy();

      void read_from_json(const QJsonObject &json);
      void write_to_json(QJsonObject &json) const;

      virtual ~philosophy();

    private:
      unsigned int _value;
      QString _name;
    };
  }
}
