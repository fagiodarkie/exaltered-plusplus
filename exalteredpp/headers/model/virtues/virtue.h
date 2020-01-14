#pragma once

#include "virtue_names.h"
#include "../thirdparty/serialisable/serialisable.hpp"

namespace virtues {
  class virtue : public Serialisable
  {
  public:
    virtue(virtue_enum virtue_e, unsigned int value, virtue_rank rank);
    virtue(const std::string& serialised_data);

    virtue_enum virtue_type() const;

    virtue_rank rank() const;
    void set_rank(virtue_rank rank);

    unsigned int value() const;
    void set_value(unsigned int value);

  private:
    virtue_enum _virtue_type; int _rank;
    unsigned int _value;

    // serialisable interface
  public:
    virtual void serialisation() override;
    virtual ~virtue();
  };
}
