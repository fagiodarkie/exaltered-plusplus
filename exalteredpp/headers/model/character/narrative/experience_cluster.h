#ifndef EXPERIENCE_CLUSTER_H
#define EXPERIENCE_CLUSTER_H

#include "../../thirdparty/serialisable/serialisable.hpp"
#include "experience.h"
#include "experience_award.h"

namespace character { namespace narrative {

    class experience_cluster : public Serialisable
    {
    public:
      experience_cluster();

      virtual void serialisation() override;

      void purchase(const experience & upgrade);
      void award(const experience_award & award);

      std::vector<experience> purchases() const;
      std::vector<experience_award> awards() const;

      unsigned int total_cost() const;
      unsigned int total_awarded() const;
      unsigned int awarded_on_session(unsigned int session) const;
      unsigned int last_session() const;
      std::vector<experience_award> awards_on_session(unsigned int session) const;

      virtual ~experience_cluster();

    private:
      std::vector<experience> _experience_purchases;
      std::vector<experience_award> _experience_awards;
    };

} }
#endif // EXPERIENCE_CLUSTER_H
