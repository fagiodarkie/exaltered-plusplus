#include "power/logos.h"

#include "json_constants.h"

namespace character {
  namespace power {

    void logos::write_to_json(QJsonObject &json) const
    {
      json[serialisation::json_constants::SLOT_LOGOS] = QString::number(_logos);
      json[serialisation::json_constants::SLOT_QABBALAH] = QString::number(_qabbalah);
      json[serialisation::json_constants::SLOT_TOTAL_QABBALAH] = QString::number(_total_qabbalah);
      json[serialisation::json_constants::SLOT_ABSOLUTE_PRINCIPLE_CONNECTION] = QString::number(_absolute_principle_connection);
      json[serialisation::json_constants::SLOT_TOTAL_CIRCADIAN_RHYTM] = QString::number(_total_cyrcadian_rhytm);
      json[serialisation::json_constants::SLOT_SPENT_CIRCADIAN_POINTS] = QString::number(_spent_cyrcadian_points);
    }

    void logos::read_from_json(const QJsonObject &json)
    {
      _logos = static_cast<unsigned int>(json[serialisation::json_constants::SLOT_LOGOS]                            .toInt());
      _qabbalah = static_cast<unsigned int>(json[serialisation::json_constants::SLOT_QABBALAH]                         .toInt());
      _total_qabbalah = static_cast<unsigned int>(json[serialisation::json_constants::SLOT_TOTAL_QABBALAH]                   .toInt());
      _absolute_principle_connection = static_cast<unsigned int>(json[serialisation::json_constants::SLOT_ABSOLUTE_PRINCIPLE_CONNECTION]    .toInt());
      _total_cyrcadian_rhytm = static_cast<unsigned int>(json[serialisation::json_constants::SLOT_TOTAL_CIRCADIAN_RHYTM]            .toInt());
      _spent_cyrcadian_points = static_cast<unsigned int>(json[serialisation::json_constants::SLOT_SPENT_CIRCADIAN_POINTS]           .toInt());
    }

    logos::~logos() {}
  }
}
