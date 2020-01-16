#pragma once

#include <string>
#include "../thirdparty/serialisable/serialisable.hpp"
#include "behavioral/name_value_pair.h"

namespace ability {
  class specialisation : public Serialisable
  {
  public:
    specialisation(const std::string& name = "", unsigned int initial_value = 1);
    specialisation(const specialisation& o);
    specialisation& operator=(const specialisation& o);

    operator std::string() const;
    operator unsigned int() const;
    void operator+=(unsigned int o);

    std::string name() const;
    unsigned int value() const;

    void set_value(unsigned int new_value);
    void increase(unsigned int new_value);

    virtual void serialisation() override;

    bool operator==(const specialisation& other) const;

    virtual ~specialisation() {}

  private:
    std::string _name;
    unsigned int _value;

  };

  static auto filter_specialisation_by_name = [](const std::string& specname) {
      return [specname](const specialisation& spec) { return spec.name() == specname; };
    };

}
