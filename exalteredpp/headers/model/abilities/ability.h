#pragma once

#include "ability_names.h"
#include "specialisation.h"
#include "../thirdparty/serialisable/serialisable.hpp"

namespace ability
{

  class ability : public Serialisable
  {
  public:
    ability();
    ability(const ability_name& name, unsigned int value = 0);
    ability(const ability& o);
    ability& operator=(const ability& o);

    operator unsigned int() const;
    operator std::string() const;
    operator ability_name() const;
    unsigned int operator+(unsigned int other) const;
    int operator+(int other) const;
    double operator+(double other) const;
    void operator=(unsigned int new_value);
    void operator+=(unsigned int new_value);
    void operator-=(unsigned int new_value);
    void operator++();
    void operator--();

    bool operator<(const ability& other) const;

    ability_name name() const;

    unsigned int value() const;
    bool favored() const;

    void set_value(unsigned int new_value);
    void set_favored(bool favored = true);

    std::vector<specialisation> specialisations() const;
    class specialisation get(const std::string& name) const;
    class specialisation& get(const std::string& name);

    int operator[](const std::string& specialisation_name) const;

    bool has(const std::string& specialisation_name) const;
    void add(const class specialisation& new_specialisation);
    void add(std::string&& new_specialisation_name, unsigned int initial_value);
    void set(const std::string& specialisation_name, unsigned int new_value);
    void increase(const std::string& specialisation_name, unsigned int add_value = 1);
    void remove(const std::string& specialisation_to_remove);

    bool operator==(const ability& other) const;

    virtual ~ability() {}
    virtual void serialisation() override;

  private:
    ability_name _name;
    unsigned int _value;
    bool _favourite;
    std::vector<class specialisation> _specialisations;
  };

  static auto ability_name_getter = [](const ability& ab) { return ab.name(); };

  static auto filter_ability_by_name = [](const std::string& subability) {
      return [subability](const ability& ab) { return ab.name().subability == subability; };
    };

  static auto filter_ability_by_ability_name = [](const ability_name& subability) {
      return [subability](const ability& ab) { return ab.name() == subability; };
    };

  static auto filter_ability_by_ability_type = [](const ability_enum& type) {
      return [type](const ability& ab) { return ab.name().ability_type == type; };
    };

  static auto ability_order_comparison = [](class ability ab1, class ability ab2) {
      return (ab1.name().ability_type < ab2.name().ability_type)
          || (ab1.name().ability_type == ab2.name().ability_type && ab1.name().subability < ab2.name().subability);
    };
}
