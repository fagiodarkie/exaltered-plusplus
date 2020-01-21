#ifndef DICE_THROWER_H
#define DICE_THROWER_H

#include "dice_roller_options.h"
#include "abstract_dice_roller.h"

#include <type_traits>
#include <random>

namespace dice {

  template<typename brutal_type = no_brutal, typename ten_rule = mortal_10_rule>
  class dice_roller : public abstract_dice_roller
  {
    static_assert(std::is_base_of<abstract_brutal, brutal_type>::value, "provided brutal_type is not base of abstract_brutal");
    static_assert(std::is_base_of<abstract_10_rule, ten_rule>::value, "provided ten_rule is not base of abstract_10_rule");

  public:

    dice_roller(unsigned int dice_number)
      : abstract_dice_roller (10, dice_number) { }

    unsigned int throw_dice() const
    {
      std::mt19937 _random = std::mt19937(std::random_device()());
      std::uniform_int_distribution<unsigned int> _distribution = std::uniform_int_distribution<unsigned int>(1, 10);
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

    virtual ~dice_roller() {}

  protected:
    brutal_type _brutal;
    ten_rule _tenrule;
  };
}

#endif // DICE_THROWER_H
