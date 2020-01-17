#ifndef EXPERIENCE_AWARD_H
#define EXPERIENCE_AWARD_H

#include "../../thirdparty/serialisable/serialisable.hpp"
#include "experience_defines.h"

namespace narrative {

    class experience_award : public Serialisable
    {
    public:
      experience_award(experience_award_type award_type = PLAYTIME, unsigned int amount = 0);

      experience_award_type type() const;
      unsigned int amount() const;
      std::string description() const;
      std::string summary() const;

      void set_description(const std::string& description);

      virtual void serialisation() override;

      virtual ~experience_award();

    private:
      experience_award_type _award_type;
      unsigned int _amount;
      std::string _description;
    };

}

#endif // EXPERIENCE_AWARD_H
