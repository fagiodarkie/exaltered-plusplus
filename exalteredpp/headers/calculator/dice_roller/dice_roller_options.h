#ifndef DICE_THROWER_OPTIONS_H
#define DICE_THROWER_OPTIONS_H

namespace dice {

  // ==== Damage reroll Ruleset ====

  class abstract_brutal {
  public:
    virtual bool should_rethrow(unsigned int die_roll) const = 0;
    virtual ~abstract_brutal() {}
  };

  class no_brutal : public abstract_brutal {
  public:
    bool should_rethrow(unsigned int ) const override { return false; }
    virtual ~no_brutal() override {}
  };

  class bashing_brutal : public abstract_brutal {
  public:
    bool should_rethrow(unsigned int ) const override { return false; }
    virtual ~bashing_brutal() override {}
  };

  class lethal_brutal : public abstract_brutal {
  public:
    bool should_rethrow(unsigned int die_roll) const override { return die_roll == 1; }
    virtual ~lethal_brutal() override {}
  };

  class aggravated_brutal : public abstract_brutal {
  public:
    bool should_rethrow(unsigned int die_roll) const override { return die_roll <= 3; }
    virtual ~aggravated_brutal() override {}
  };

  // ==== Success value Ruleset ====

  class abstract_10_rule {
  public:
    virtual unsigned int ten_rolled_value() const = 0;
    virtual unsigned int success(unsigned int die) const = 0;
    virtual ~abstract_10_rule() {}
  };

  class mortal_10_rule : public abstract_10_rule {
  public:
    unsigned int ten_rolled_value() const override { return 1; }
    unsigned int success(unsigned int die) const override
    {
      return die >= 7 ? 1 : 0;
    }

    virtual ~mortal_10_rule() override {}
  };

  template<unsigned int threshold = 7, unsigned int ten_value = 2>
  class exalt_10_rule : public abstract_10_rule {
  public:
    unsigned int ten_rolled_value() const override { return ten_value; }
    unsigned int success(unsigned int die) const override
    {
      return die >= threshold ? 1 : ten_rolled_value();
    }

    virtual ~exalt_10_rule() override {}
  };

  unsigned int roll_result(int result);
  unsigned int pool(int result);

}

#endif // DICE_THROWER_OPTIONS_H
