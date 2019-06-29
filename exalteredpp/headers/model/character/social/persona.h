#pragma once

#include "serialisable.h"
#include "philosophy.h"

#include <QList>

namespace character {
  namespace social {
    class persona : public serialisable
    {
    public:
      persona();

      void read_from_json(const QJsonObject &json);
      void write_to_json(QJsonObject &json) const;

      virtual ~persona();

    private:
      QList<philosophy> _philosophies;


    };
  }
}
