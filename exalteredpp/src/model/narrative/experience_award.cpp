#include "narrative/experience_award.h"

#include "json_constants.h"

namespace narrative {

    experience_award::experience_award(experience_award_type award_type, unsigned int amount)
      : _award_type(award_type), _amount(amount) { }

    experience_award::~experience_award() { }

    void experience_award::set_description(const std::string &description)
    {
      _description = description;
    }

    experience_award_type experience_award::type() const
    {
      return _award_type;
    }

    void experience_award::serialisation()
    {
      synch(serialisation::json_constants::SLOT_TYPE, _award_type);
      synch(serialisation::json_constants::SLOT_AMOUNT, _amount);
      synch(serialisation::json_constants::SLOT_DESCRIPTION, _description);
    }

    std::string experience_award::description() const
    {
      return _description;
    }

    unsigned int experience_award::amount() const
    {
      return _amount;
    }

    std::string experience_award::summary() const
    {
      char award[4];
      sprintf(award, "%d", _amount);

      std::string desc = _description.empty() ? "" : (" (" + _description + ")");
      return AWARD_NAME.at(_award_type) + ": +"
          + award + desc;
    }


}
