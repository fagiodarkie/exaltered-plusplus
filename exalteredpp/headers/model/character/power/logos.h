#pragma once

#include "serialisable.h"

namespace character {
  namespace power {
    class logos : public serialisable
    {
    public:

      logos(unsigned int logos = 1, unsigned int qabbalah = 0, unsigned int total_qabbalah = 0, unsigned int absolute_connection = 0, unsigned int total_cyrcadian_rhythm = 0, unsigned int spent_cyrcadian_points = 0);

      void read_from_json(const QJsonObject &json);
      void write_to_json(QJsonObject &json) const;

      unsigned int get_logos() const;
      unsigned int get_current_qabbalah() const;
      unsigned int get_total_qabbalah() const;
      unsigned int get_absolute_principle_connection() const;
      unsigned int get_total_cyrcadian_rhythm() const;
      unsigned int get_current_cyrcadian_rhythm() const;

      virtual ~logos();

    private:
      unsigned int _logos, _qabbalah, _total_qabbalah,
        _absolute_principle_connection,
        _total_cyrcadian_rhythm, _spent_cyrcadian_points;
    };
  }
}

