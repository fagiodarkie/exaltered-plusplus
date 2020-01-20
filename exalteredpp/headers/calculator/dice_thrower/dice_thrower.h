#ifndef DICE_THROWER_H
#define DICE_THROWER_H

#include "dice_thrower_options.h"
#include "abstract_dice_thrower.h"

#include <type_traits>
#include <random>

namespace dice {

  template<typename brutal_type = no_brutal, typename ten_rule = mortal_10_rule>
  class dice_thrower : public abstract_dice_thrower
  {
    static_assert(std::is_base_of<brutal_type, abstract_brutal>::value, "provided brutal_type is not base of abstract_brutal");
    static_assert(std::is_base_of<ten_rule, abstract_10_rule>::value, "provided ten_rule is not base of abstract_10_rule");

  public:

    dice_thrower(unsigned int dice_number)
      : abstract_dice_thrower (10, dice_number)
    {
      std::random_device randev;
      _random = std::mt19937(randev());
      _distribution = std::uniform_int_distribution<unsigned int>(1, 10);
    }

    unsigned int throw_dice() const
    {
      unsigned int result = 0, die = 0;
      for (unsigned int i = 0; i < _die_number; ++i)
        {
          do {
              die = _distribution(_random);
            }
          while (_brutal.should_rethrow(die));
          result += _tenrule.success(die);
        }

      return result;
    }

    virtual ~dice_thrower() {}

  private:
    brutal_type _brutal;
    ten_rule _tenrule;
    std::uniform_int_distribution<unsigned int> _distribution;
    std::mt19937 _random;
  };

}

#endif // DICE_THROWER_H
