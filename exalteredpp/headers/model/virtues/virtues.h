#pragma once

#include "virtues/virtue.h"
#include <list>
#include "../thirdparty/serialisable/serialisable.hpp"

namespace virtues {
  class virtues : public std::vector<virtue>, public Serialisable
  {
  public:
    virtues();

    virtue& value(virtue_enum virtue_name);
    virtue& operator[](int index);

    virtue value(virtue_enum virtue_name) const;
    virtue operator[](int index) const;

    void set_vice_type(vice_enum vice_name);
    void set_vice_value(unsigned int value);

    vice_enum vice() const;
    unsigned int vice_value() const;

    virtual void serialisation() override;
    virtual ~virtues();

  private:
    int _vice;
    unsigned int _vice_value;
  };
}

