#ifndef ABSTRACT_PURCHASE_H
#define ABSTRACT_PURCHASE_H

#include <memory>
#include <string>
#include "../../thirdparty/serialisable/serialisable.hpp"

namespace character {

  class character;
  namespace narrative {

    class abstract_purchase : public Serialisable
    {
    public:

      virtual void apply(std::shared_ptr<character>) = 0;

      virtual void serialisation() override = 0;

      virtual std::string description() const = 0;
      virtual std::string key() const = 0;

      virtual ~abstract_purchase() {}
    };

}}
#endif // ABSTRACT_PURCHASE_H
