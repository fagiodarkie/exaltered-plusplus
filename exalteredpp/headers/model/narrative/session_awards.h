#ifndef SESSION_AWARDS_H
#define SESSION_AWARDS_H


#include "../../thirdparty/serialisable/serialisable.hpp"
#include "experience.h"
#include "experience_award.h"

namespace narrative {

    class session_awards : public Serialisable, public std::map<experience_award_type, experience_award>
    {
    public:

      void serialisation() override;

      virtual ~session_awards() {}
    };
}
#endif // SESSION_AWARDS_H
