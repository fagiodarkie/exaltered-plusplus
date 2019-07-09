#include "power/logos.h"

#include "json_constants.h"

namespace character {
  namespace power {

    logos::logos(unsigned int logos, unsigned int qabbalah, unsigned int total_qabbalah, unsigned int absolute_connection,
                 unsigned int total_cyrcadian_rhythm, unsigned int spent_cyrcadian_points)
      : _logos(logos), _qabbalah(qabbalah), _total_qabbalah(total_qabbalah), _absolute_principle_connection(absolute_connection),
          _total_cyrcadian_rhythm(total_cyrcadian_rhythm), _spent_cyrcadian_points(spent_cyrcadian_points) { }

    unsigned int logos::get_logos() const
    {
      return _logos;
    }

    unsigned int logos::get_total_qabbalah() const
    {
      return _total_qabbalah;
    }

    unsigned int logos::get_current_qabbalah() const
    {
      return _qabbalah;
    }

    unsigned int logos::get_total_cyrcadian_rhythm() const
    {
      return _total_cyrcadian_rhythm;
    }

    unsigned int logos::get_current_cyrcadian_rhythm() const
    {
      return _total_cyrcadian_rhythm - _spent_cyrcadian_points;
    }

    unsigned int logos::get_absolute_principle_connection() const
    {
      return _absolute_principle_connection;
    }

    void logos::write_to_json(QJsonObject &json) const
    {
      json[serialisation::json_constants::SLOT_LOGOS] = QString::number(_logos);
      json[serialisation::json_constants::SLOT_QABBALAH] = QString::number(_qabbalah);
      json[serialisation::json_constants::SLOT_TOTAL_QABBALAH] = QString::number(_total_qabbalah);
      json[serialisation::json_constants::SLOT_ABSOLUTE_PRINCIPLE_CONNECTION] = QString::number(_absolute_principle_connection);
      json[serialisation::json_constants::SLOT_TOTAL_CIRCADIAN_RHYTHM] = QString::number(_total_cyrcadian_rhythm);
      json[serialisation::json_constants::SLOT_SPENT_CIRCADIAN_POINTS] = QString::number(_spent_cyrcadian_points);
    }

    void logos::read_from_json(const QJsonObject &json)
    {
      _logos = static_cast<unsigned int>(json[serialisation::json_constants::SLOT_LOGOS]                                                .toString().toInt());
      _qabbalah = static_cast<unsigned int>(json[serialisation::json_constants::SLOT_QABBALAH]                                          .toString().toInt());
      _total_qabbalah = static_cast<unsigned int>(json[serialisation::json_constants::SLOT_TOTAL_QABBALAH]                              .toString().toInt());
      _absolute_principle_connection = static_cast<unsigned int>(json[serialisation::json_constants::SLOT_ABSOLUTE_PRINCIPLE_CONNECTION].toString().toInt());
      _total_cyrcadian_rhythm = static_cast<unsigned int>(json[serialisation::json_constants::SLOT_TOTAL_CIRCADIAN_RHYTHM]              .toString().toInt());
      _spent_cyrcadian_points = static_cast<unsigned int>(json[serialisation::json_constants::SLOT_SPENT_CIRCADIAN_POINTS]              .toString().toInt());
    }

    logos::~logos() {}
  }
}
