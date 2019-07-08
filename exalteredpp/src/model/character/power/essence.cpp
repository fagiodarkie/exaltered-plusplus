#include "power/essence.h"

#include "json_constants.h"

namespace character {
  namespace power {

    essence::essence() : _permanent_essence(1),
                         _khan(1),
                         _celestial_portion(0),
                         _personal_committed_essence(0),
                         _personal_spent_essence(0),
                         _peripheral_committed_essence(0),
                         _peripheral_spent_essence(0),
                         _spiritual_committed_essence(0),
                         _spiritual_spent_essence(0),
                         _total_personal_essence(0),
                         _total_peripheral_essence(0),
                         _total_spiritual_essence(0),
                         _bonus_personal_essence(0),
                         _bonus_peripheral_essence(0),
                         _bonus_spiritual_essence(0) {}

    unsigned int essence::permanent_essence() const
    {
      return _permanent_essence;
    }

    unsigned int essence::khan() const
    {
      return _khan;
    }

    void essence::set_khan(unsigned int khan)
    {
      _khan = khan;
    }

    void essence::set_permanent_essence(unsigned int permanent_essence)
    {
      _permanent_essence = permanent_essence;
    }

    unsigned int essence::available_personal_essence() const
    {
      return total_personal_essence() - _personal_committed_essence - _personal_spent_essence;
    }

    unsigned int essence::available_peripheral_essence() const
    {
      return total_peripheral_essence() - _peripheral_committed_essence - _peripheral_spent_essence;
    }

    unsigned int essence::available_spiritual_essence() const
    {
      return total_spiritual_essence() - _spiritual_committed_essence - _spiritual_spent_essence;
    }

    unsigned int essence::total_personal_essence() const
    {
      return _total_personal_essence + _bonus_personal_essence;
    }

    unsigned int essence::total_peripheral_essence() const
    {
      return _total_peripheral_essence + _bonus_peripheral_essence;
    }

    unsigned int essence::total_spiritual_essence() const
    {
      return _total_spiritual_essence + _bonus_spiritual_essence;
    }


    void essence::commit_essence(unsigned int commit_essence)
    {
      if (available_personal_essence() > commit_essence)
        {
          _personal_committed_essence += commit_essence;
          return;
        }

      unsigned int to_be_committed_in_peripheral = commit_essence - available_personal_essence();
      _personal_committed_essence += available_personal_essence();
      _peripheral_committed_essence += to_be_committed_in_peripheral;
    }

    void essence::commit_spiritual_essence(unsigned int commit_essence)
    {
      _spiritual_committed_essence += commit_essence > available_spiritual_essence() ? available_spiritual_essence() : commit_essence;
    }

    void essence::decommit_essence(unsigned int commit_essence)
    {
      if (_peripheral_committed_essence >= commit_essence)
        {
          _peripheral_committed_essence -= commit_essence;
          return;
        }

      unsigned int to_be_decommitted_from_personal = commit_essence - _peripheral_committed_essence;
      _peripheral_committed_essence = 0;
      _personal_committed_essence = to_be_decommitted_from_personal > _personal_committed_essence ? 0 : _personal_committed_essence - to_be_decommitted_from_personal;
    }

    void essence::decommit_spiritual_essence(unsigned int commit_essence)
    {
      _spiritual_committed_essence = commit_essence > _spiritual_committed_essence ? 0 : _spiritual_committed_essence - commit_essence;
    }

    bool essence::can_spend_essence(unsigned int essence) const
    {
      return available_personal_essence() + available_peripheral_essence() >= essence;
    }

    bool essence::can_spend_spiritual_essence(unsigned int essence) const
    {
      return available_spiritual_essence() >= essence;
    }

    void essence::spend_essence(unsigned int essence)
    {
      if (available_personal_essence() >= essence)
        {
          _personal_spent_essence += essence;
          return;
        }

      unsigned int to_be_spent_in_peripheral = essence - available_personal_essence();
      _personal_spent_essence += available_personal_essence();
      _peripheral_spent_essence += to_be_spent_in_peripheral > available_peripheral_essence() ? available_peripheral_essence() : to_be_spent_in_peripheral;
    }

    void essence::spend_spiritual_essence(unsigned int essence)
    {
      _spiritual_spent_essence += essence <= available_spiritual_essence() ? essence : available_spiritual_essence();
    }

    void essence::recover_essence(unsigned int essence)
    {
      if (_peripheral_spent_essence >= essence)
        {
          _peripheral_spent_essence -= essence;
          return;
        }

      unsigned int to_be_recovered_from_personal = essence - _peripheral_spent_essence;
      _peripheral_spent_essence = 0;
      _personal_spent_essence = to_be_recovered_from_personal > _personal_spent_essence ? 0 : _personal_spent_essence - to_be_recovered_from_personal;
    }

    void essence::recover_spiritual_essence(unsigned int essence)
    {
      _spiritual_spent_essence = essence > _spiritual_spent_essence ? 0 : _spiritual_spent_essence - essence;
    }


    void essence::set_bonus_personal_essence(unsigned int essence)
    {
      _bonus_personal_essence = essence;
    }

    void essence::set_bonus_peripheral_essence(unsigned int essence)
    {
      _bonus_peripheral_essence = essence;
    }

    void essence::set_bonus_spiritual_essence(unsigned int essence)
    {
      _bonus_spiritual_essence = essence;
    }


    void essence::read_from_json(const QJsonObject &json)
    {
      _permanent_essence              = static_cast<unsigned int>(json[serialisation::json_constants::SLOT_ESSENCE_PERMANENT]            .toString().toInt());
      _khan                           = static_cast<unsigned int>(json[serialisation::json_constants::SLOT_ESSENCE_KHAN]                 .toString().toInt());
      _celestial_portion              = static_cast<unsigned int>(json[serialisation::json_constants::SLOT_ESSENCE_CELESTIAL_PORTION]    .toString().toInt());
      _personal_committed_essence     = static_cast<unsigned int>(json[serialisation::json_constants::SLOT_ESSENCE_PERSONAL_COMMITTED]   .toString().toInt());
      _personal_spent_essence         = static_cast<unsigned int>(json[serialisation::json_constants::SLOT_ESSENCE_PERSONAL_SPENT]       .toString().toInt());
      _peripheral_committed_essence   = static_cast<unsigned int>(json[serialisation::json_constants::SLOT_ESSENCE_PERIPHERAL_COMMITTED] .toString().toInt());
      _peripheral_spent_essence       = static_cast<unsigned int>(json[serialisation::json_constants::SLOT_ESSENCE_PERIPHERAL_SPENT]     .toString().toInt());
      _spiritual_committed_essence    = static_cast<unsigned int>(json[serialisation::json_constants::SLOT_ESSENCE_SPIRITUAL_COMMITTED]  .toString().toInt());
      _spiritual_spent_essence        = static_cast<unsigned int>(json[serialisation::json_constants::SLOT_ESSENCE_SPIRITUAL_SPENT]      .toString().toInt());
      _total_personal_essence         = static_cast<unsigned int>(json[serialisation::json_constants::SLOT_ESSENCE_PERSONAL_TOTAL]       .toString().toInt());
      _total_peripheral_essence       = static_cast<unsigned int>(json[serialisation::json_constants::SLOT_ESSENCE_PERIPHERAL_TOTAL]     .toString().toInt());
      _total_spiritual_essence        = static_cast<unsigned int>(json[serialisation::json_constants::SLOT_ESSENCE_SPIRITUAL_TOTAL]      .toString().toInt());
      _bonus_personal_essence         = static_cast<unsigned int>(json[serialisation::json_constants::SLOT_ESSENCE_PERSONAL_BONUS]       .toString().toInt());
      _bonus_peripheral_essence       = static_cast<unsigned int>(json[serialisation::json_constants::SLOT_ESSENCE_PERIPHERAL_BONUS]     .toString().toInt());
      _bonus_spiritual_essence        = static_cast<unsigned int>(json[serialisation::json_constants::SLOT_ESSENCE_SPIRITUAL_BONUS]      .toString().toInt());
    }

    void essence::write_to_json(QJsonObject &json) const
    {
      json[serialisation::json_constants::SLOT_ESSENCE_PERMANENT]            = QString::number(_permanent_essence           );
      json[serialisation::json_constants::SLOT_ESSENCE_KHAN]                 = QString::number(_khan                        );
      json[serialisation::json_constants::SLOT_ESSENCE_CELESTIAL_PORTION]    = QString::number(_celestial_portion           );
      json[serialisation::json_constants::SLOT_ESSENCE_PERSONAL_COMMITTED]   = QString::number(_personal_committed_essence  );
      json[serialisation::json_constants::SLOT_ESSENCE_PERSONAL_SPENT]       = QString::number(_personal_spent_essence      );
      json[serialisation::json_constants::SLOT_ESSENCE_PERIPHERAL_COMMITTED] = QString::number(_peripheral_committed_essence);
      json[serialisation::json_constants::SLOT_ESSENCE_PERIPHERAL_SPENT]     = QString::number(_peripheral_spent_essence    );
      json[serialisation::json_constants::SLOT_ESSENCE_SPIRITUAL_COMMITTED]  = QString::number(_spiritual_committed_essence );
      json[serialisation::json_constants::SLOT_ESSENCE_SPIRITUAL_SPENT]      = QString::number(_spiritual_spent_essence     );
      json[serialisation::json_constants::SLOT_ESSENCE_PERSONAL_TOTAL]       = QString::number(_total_personal_essence      );
      json[serialisation::json_constants::SLOT_ESSENCE_PERIPHERAL_TOTAL]     = QString::number(_total_peripheral_essence    );
      json[serialisation::json_constants::SLOT_ESSENCE_SPIRITUAL_TOTAL]      = QString::number(_total_spiritual_essence     );
      json[serialisation::json_constants::SLOT_ESSENCE_PERSONAL_BONUS]       = QString::number(_bonus_personal_essence      );
      json[serialisation::json_constants::SLOT_ESSENCE_PERIPHERAL_BONUS]     = QString::number(_bonus_peripheral_essence    );
      json[serialisation::json_constants::SLOT_ESSENCE_SPIRITUAL_BONUS]      = QString::number(_bonus_spiritual_essence     );
    }

    void essence::set_celestial_portion(unsigned int celestial_portion)
    {
      _celestial_portion = celestial_portion;
    }

    unsigned int essence::get_celestial_portion_percentage() const
    {
      return _celestial_portion;
    }

    unsigned int essence::get_terrestrial_portion_percentage() const
    {
      return 100 - _celestial_portion;
    }

    essence::~essence() {}

    void essence::set_total_personal_essence(unsigned int total_personal_essence)
    {
      _total_personal_essence = total_personal_essence;
    }

    void essence::set_total_peripheral_essence(unsigned int total_peripheral_essence)
    {
      _total_peripheral_essence = total_peripheral_essence;
    }

    void essence::set_total_spiritual_essence(unsigned int total_spiritual_essence)
    {
      _total_spiritual_essence = total_spiritual_essence;
    }
  }
}
