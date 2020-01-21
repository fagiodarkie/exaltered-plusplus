#ifndef DICEROLLER_MOCK_H
#define DICEROLLER_MOCK_H

#include "dice_roller/abstract_dice_roller.h"
#include <cmath>

class mock_diceroller : public dice::abstract_dice_roller
{
public:
  mock_diceroller() : dice::abstract_dice_roller(10, 1) {}

  unsigned int throw_dice() const
  {
    return std::floor((float)_die_number * _success_ratio);
  }

  void set_ratio(float success_ratio)
  {
    _success_ratio = success_ratio;
  }

  virtual ~mock_diceroller() {}

private:
  float _success_ratio = 0.3f;
};


#endif // DICEROLLER_MOCK_H
