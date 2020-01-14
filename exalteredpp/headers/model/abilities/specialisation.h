#pragma once

#include <string>
#include "../thirdparty/serialisable/serialisable.hpp"
#include "behavioral/name_value_pair.h"

namespace ability {
  class specialisation : public model::name_value_pair, public Serialisable
  {
  public:
    specialisation(const std::string& name = "", unsigned int initial_value = 1);
    specialisation(const specialisation& o);
    specialisation& operator=(const specialisation& o);

    std::string get_name() const override;
    std::string get_value() const override;
    unsigned int get_specialisation_value() const;

    void set_value(unsigned int new_value);

    virtual void serialisation() override;

    bool operator==(const specialisation& other) const;

  private:
    std::string name;
    unsigned int value;

  };
}
