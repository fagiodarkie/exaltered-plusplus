#ifndef EXPERIENCE_H
#define EXPERIENCE_H

#include "../../thirdparty/serialisable/serialisable.hpp"
#include "experience_defines.h"
#include "abstract_purchase.h"

namespace character { namespace narrative {

    class experience : public Serialisable
    {
    public:
      experience(experience_expense_type expense_type = CHARM, unsigned int cost = 0, std::shared_ptr<abstract_purchase> purchase = nullptr);

      void serialisation() override;

      unsigned int cost() const;
      experience_expense_type purchase_type() const;
      std::shared_ptr<abstract_purchase> purchase() const;

      virtual ~experience();

    private:
      experience_expense_type _expense_type;
      unsigned int _cost;
      std::shared_ptr<abstract_purchase> _purchase;
    };

}  }

#endif // EXPERIENCE_H
