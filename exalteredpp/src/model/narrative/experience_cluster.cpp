#include "narrative/experience_cluster.h"
#include "json_constants.h"
#include <algorithm>

namespace narrative {

    experience_cluster::experience_cluster() { }

    experience_cluster::~experience_cluster() { }

    void experience_cluster::serialisation()
    {
      synch(serialisation::json_constants::SLOT_PURCHASES, _experience_purchases);
      synch(serialisation::json_constants::SLOT_AWARDS, _experience_awards);
    }

    void experience_cluster::purchase(const experience_purchase &upgrade)
    {
      _experience_purchases.push_back(upgrade);
    }

    void experience_cluster::award(const session_awards &award)
    {
      _experience_awards.push_back(award);
    }

    unsigned int experience_cluster::last_session() const
    {
      return _experience_awards.size();
    }

    std::vector<experience_purchase> experience_cluster::purchases() const
    {
      return _experience_purchases;
    }

    std::vector<session_awards> experience_cluster::awards() const
    {
      return _experience_awards;
    }

    unsigned int experience_cluster::total_cost() const
    {
      unsigned int total = 0;
      for (auto exp: _experience_purchases)
        total += exp.cost();

      return total;
    }

    unsigned int experience_cluster::total_awarded() const
    {
      unsigned int total = 0;
      for (auto session: _experience_awards)
      for (auto exp: session)
        total += exp.second.amount();

      return total;
    }

    unsigned int experience_cluster::awarded_on_session(unsigned int session) const
    {
      unsigned int total = 0;
      for (auto exp: awards_on_session(session))
        total += exp.second.amount();

      return total;
    }

    session_awards experience_cluster::awards_on_session(unsigned int session) const
    {
      if (session > 0)
        return _experience_awards.at(session - 1);

      return session_awards();
    }


}
