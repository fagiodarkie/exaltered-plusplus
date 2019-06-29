#pragma once

#include "serialisable.h"

namespace character {
  namespace power {
    class logos : public serialisable
    {
    public:
      logos();

      void read_from_json(const QJsonObject &json);
      void write_to_json(QJsonObject &json) const;

      virtual ~logos();

    private:
      unsigned int _logos, _qabbalah, _total_qabbalah, _absolute_principle_connection,
        _total_cyrcadian_rhytm, _spent_cyrcadian_points;
    };
  }
}

