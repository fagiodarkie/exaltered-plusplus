#include "power/logos.h"
#include "errors/invalid_parameter.h"

#include "json_constants.h"

namespace power {

  logos::logos(unsigned int logos, unsigned int qabbalah, unsigned int total_qabbalah, unsigned int absolute_connection,
               unsigned int total_cyrcadian_rhythm, unsigned int spent_cyrcadian_points)
    : _logos(logos), _qabbalah(qabbalah), _total_qabbalah(total_qabbalah), _absolute_principle_connection(absolute_connection),
        _total_cyrcadian_rhythm(total_cyrcadian_rhythm), _spent_cyrcadian_points(spent_cyrcadian_points) { }

  unsigned int logos::get_logos() const
  {
    return _logos;
  }

  void logos::set_logos(unsigned int value)
  {
    if (value > 6)
      throw exception::invalid_parameter();

    _logos = value;
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

  void logos::serialisation()
  {
    synch(serialisation::json_constants::SLOT_LOGOS                        , _logos                        );
    synch(serialisation::json_constants::SLOT_QABBALAH                     , _qabbalah                     );
    synch(serialisation::json_constants::SLOT_TOTAL_QABBALAH               , _total_qabbalah               );
    synch(serialisation::json_constants::SLOT_ABSOLUTE_PRINCIPLE_CONNECTION, _absolute_principle_connection);
    synch(serialisation::json_constants::SLOT_TOTAL_CIRCADIAN_RHYTHM       , _total_cyrcadian_rhythm       );
    synch(serialisation::json_constants::SLOT_SPENT_CIRCADIAN_POINTS       , _spent_cyrcadian_points       );
  }

  logos::~logos() {}
}
