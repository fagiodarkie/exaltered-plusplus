#include "narrative/experience_cluster.h"

namespace character { namespace narrative {

    experience_cluster::experience_cluster() { }

    experience_cluster::~experience_cluster() { }

    void experience_cluster::serialisation()
    {
      synch("purchases", _experience_purchases);
      synch("awards", _experience_awards);
    }

    void experience_cluster::purchase(const experience &upgrade)
    {
      _experience_purchases.push_back(upgrade);
    }

    void experience_cluster::award(const experience_award &award)
    {
      _experience_awards.push_back(award);
    }

    std::vector<experience> experience_cluster::purchases() const
    {
      return _experience_purchases;
    }

    std::vector<experience_award> experience_cluster::awards() const
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
      for (auto exp: _experience_awards)
        total += exp.amount();

      return total;
    }

    unsigned int experience_cluster::awarded_on_session(unsigned int session) const
    {
      unsigned int total = 0;
      for (auto exp: _experience_awards)
        if (exp.session() == session)
          total += exp.amount();

      return total;
    }

    std::vector<experience_award> experience_cluster::awards_on_session(unsigned int session) const
    {
      std::vector<experience_award> result;

      for (auto exp: _experience_awards)
        if (exp.session() == session)
          result.push_back(exp);

      return result;
    }


} }
