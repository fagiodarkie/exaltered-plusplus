#include "virtues/virtue.h"
#include "json_constants.h"
#include "common/reverse_search.h"

namespace character {
  namespace virtues {

    using namespace serialisation;

    virtue::virtue(QJsonObject object)
    {
      read_from_json(object);
    }

    virtue::virtue(virtue_enum virtue_e, unsigned int value, virtue_rank rank)
      : _virtue_type(virtue_e), _rank(rank), _value(value)
    { }

    virtue_enum virtue::virtue_type() const
    {
      return _virtue_type;
    }

    virtue_rank virtue::rank() const
    {
      return _rank;
    }

    void virtue::set_rank(virtue_rank rank)
    {
      _rank = rank;
    }

    unsigned int virtue::value() const
    {
      return _value;
    }

    void virtue::set_value(unsigned int value)
    {
      _value = value;
    }

    void virtue::read_from_json(const QJsonObject &json)
    {
      QString virtue_name = json[json_constants::SLOT_NAME].toString(),
          virtue_rank = json[json_constants::SLOT_RANK].toString();
      unsigned int virtue_value = static_cast<unsigned int>(json[json_constants::SLOT_VALUE].toString().toInt());

      _virtue_type = commons::reverse_search_in_map(VIRTUE_LIST, VIRTUE_NAME, virtue_name);
      _rank = commons::reverse_search_in_map(VIRTUE_RANK_LIST, RANK_NAME, virtue_rank);
      _value = virtue_value;
    }

    void virtue::write_to_json(QJsonObject &json) const
    {
      json[json_constants::SLOT_NAME] = VIRTUE_NAME.value(_virtue_type);
      json[json_constants::SLOT_RANK] = RANK_NAME.value(_rank);
      json[json_constants::SLOT_VALUE] = QString::number(_value);
    }

    virtue::~virtue() {};
  }
}
