#pragma once

#include "behavioral/name_value_pair.h"

namespace character
{

  class ability : public model::name_value_pair
  {
  public:
    ability(const QString& name, int value = 0);

    operator int() const;
    operator QString() const;

    QString get_name() const override;
    QString get_value() const override;

    virtual ~ability() override = default;

  private:
    QString _name;
    int _value;
  };

}
