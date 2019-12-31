#include "narrative/experience_award.h"

#include "json_constants.h"

namespace character { namespace narrative {

    experience_award::experience_award(experience_award_type award_type, unsigned int amount, unsigned int session_number)
      : _award_type(award_type), _amount(amount), _session_number(session_number) { }

    experience_award::~experience_award() { }

    void experience_award::set_description(const std::string &description)
    {
      _description = description;
    }

    void experience_award::serialisation()
    {
      synch(serialisation::json_constants::SLOT_TYPE, _award_type);
      synch(serialisation::json_constants::SLOT_AMOUNT, _amount);
      synch(serialisation::json_constants::SLOT_SESSION, _session_number);
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

    unsigned int experience_award::session() const
    {
      return _session_number;
    }

    std::string experience_award::summary() const
    {
      char award[8], session[8];
      sprintf(award, "%d", _amount);
      sprintf(session, "%d", _session_number);

      std::string desc = _description.empty() ? "" : (" (" + _description + ")");
      return AWARD_NAME.at(_award_type) + " (#" + session + "): +"
          + award + desc;
    }


}}
