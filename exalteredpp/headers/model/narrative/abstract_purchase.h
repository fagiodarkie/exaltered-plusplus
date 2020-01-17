#ifndef ABSTRACT_PURCHASE_H
#define ABSTRACT_PURCHASE_H

#include <memory>
#include <string>

namespace character {

  class character;
}

namespace narrative {

  class abstract_purchase
  {
  public:

    virtual void apply(std::shared_ptr<character::character>) = 0;

    virtual std::string description() const = 0;
    virtual std::string key() const = 0;
    virtual unsigned int amount() const = 0;
    virtual ~abstract_purchase() {}

  protected:
    std::string progress(unsigned int new_value) const
    {
      if (new_value == 0)
        return "0";

      char oldval[2], newval[2];
      sprintf(oldval, "%d", new_value - 1);
      sprintf(newval, "%d", new_value);
      return std::string(oldval) + " -> " + newval;
    }
  };

}
#endif // ABSTRACT_PURCHASE_H
