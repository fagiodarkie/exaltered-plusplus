#pragma once

#include "virtue_names.h"
#include "../thirdparty/serialisable/serialisable.hpp"

namespace virtues {
  class virtue : public Serialisable
  {
  public:
    virtue(virtue_enum virtue_e, unsigned int value);
    virtue(const std::string& serialised_data);

    virtue_enum virtue_type() const;

    unsigned int value() const;
    void set_value(unsigned int value);

  private:
    virtue_enum _virtue_type;
    unsigned int _value;

    // serialisable interface
  public:
    virtual void serialisation() override;
    virtual ~virtue();
  };
}
