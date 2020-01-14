#ifndef EXPERIENCE_CLUSTER_H
#define EXPERIENCE_CLUSTER_H

#include "../../thirdparty/serialisable/serialisable.hpp"
#include "experience.h"
#include "experience_award.h"
#include "session_awards.h"

namespace narrative {

    class experience_cluster : public Serialisable
    {
    public:
      experience_cluster();

      virtual void serialisation() override;

      void purchase(const experience_purchase & upgrade);
      void award(const session_awards& award);

      std::vector<experience_purchase> purchases() const;
      std::vector<session_awards> awards() const;

      unsigned int total_cost() const;
      unsigned int total_awarded() const;
      unsigned int awarded_on_session(unsigned int session) const;
      unsigned int last_session() const;
      session_awards awards_on_session(unsigned int session) const;

      virtual ~experience_cluster();

    private:
      std::vector<experience_purchase> _experience_purchases;
      std::vector<session_awards> _experience_awards;
    };

}
#endif // EXPERIENCE_CLUSTER_H
