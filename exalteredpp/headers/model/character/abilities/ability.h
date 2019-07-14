#pragma once

#include "behavioral/name_value_pair.h"
#include "../thirdparty/serialisable/serialisable.hpp"

namespace character
{

  class ability : public model::name_value_pair, public Serialisable
  {
  public:
    ability();
    ability(const QString& name, unsigned int value = 0);
    ability(const ability& o);
    ability& operator=(const ability& o);

    operator unsigned int() const;
    operator QString() const;

    QString get_name() const override;
    QString get_value() const override;
    unsigned int get_ability_value() const;

    void set_value(unsigned int new_value);

    virtual void serialisation() override;

    bool operator==(const ability& other) const;

  private:
    QString _name;
    unsigned int _value;
  };

}
