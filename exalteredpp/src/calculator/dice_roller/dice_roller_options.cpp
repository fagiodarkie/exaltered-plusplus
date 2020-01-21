#include "dice_roller/dice_roller_options.h"

namespace dice {
  unsigned int roll_result(int result)
  {
    return result < 0 ? 0 : result;
  }

  unsigned int pool(int result)
  {
    return roll_result(result);
  }
}
