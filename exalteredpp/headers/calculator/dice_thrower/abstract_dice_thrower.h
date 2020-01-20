#ifndef ABSTRACT_DICE_THROWER_H
#define ABSTRACT_DICE_THROWER_H

namespace dice {

  class abstract_dice_thrower {

  public:
    virtual unsigned int throw_dice() const = 0;

    virtual void with_pool(unsigned int pool)
    {
      _die_number = pool;
    }

    virtual ~abstract_dice_thrower() {}

  protected:
    abstract_dice_thrower(unsigned int die_faces, unsigned int die_number)
      : _die_faces(die_faces), _die_number(die_number) { }

    unsigned int _die_faces, _die_number;
  };

}

#endif // ABSTRACT_DICE_THROWER_H
