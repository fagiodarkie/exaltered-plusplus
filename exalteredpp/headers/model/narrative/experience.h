#ifndef EXPERIENCE_H
#define EXPERIENCE_H

#include "../../thirdparty/serialisable/serialisable.hpp"
#include "experience_defines.h"
#include "abstract_purchase.h"
#include "json_constants.h"

namespace narrative {

    class experience_purchase : public Serialisable
    {
    public:
      experience_purchase(experience_expense_type expense_type = CHARM, unsigned int cost = 0, std::shared_ptr<abstract_purchase> purchase = nullptr);

      void serialisation() override;

      unsigned int cost() const;
      experience_expense_type purchase_type() const;
      std::shared_ptr<abstract_purchase> purchase() const;

      virtual ~experience_purchase();

    private:
      experience_expense_type _expense_type;
      unsigned int _cost;
      std::shared_ptr<abstract_purchase> _purchase;

      template<typename T>
      typename std::enable_if<std::is_base_of<abstract_purchase, T>::value, void>::type synch_purchase()
      {
        if (saving())
          {
            // saving
            auto purchase_pointer = dynamic_cast<T*>(_purchase.get());
            synch(serialisation::json_constants::SLOT_PURCHASE, purchase_pointer);
          }
        else
          {
            // loading
            T *purchase_pointer;
            synch(serialisation::json_constants::SLOT_PURCHASE, purchase_pointer);
            _purchase = std::shared_ptr<abstract_purchase>(purchase_pointer);
          }
      }
    };

}

#endif // EXPERIENCE_H
