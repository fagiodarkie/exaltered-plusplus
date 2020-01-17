#pragma once

#include "../thirdparty/serialisable/serialisable.hpp"

namespace power {
  class health : public Serialisable
  {
  public:
    health(unsigned int total_health = 0);
    health(unsigned int total_health, unsigned int current_health);

    unsigned int total_health() const;
    unsigned int current_health() const;
    void set_total_health(unsigned int total_health);
    void deal_damage(unsigned int damage);
    void heal_damage(unsigned int damage);

    double injured_health_level() const;
    double dying_health_level() const;
    unsigned int current_health_penalty() const;

    virtual void serialisation() override;
    virtual ~health();

  private:
    unsigned int _total_health, _current_health;

  };
}
