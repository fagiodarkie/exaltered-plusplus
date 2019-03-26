#pragma once

#include <QString>
#include "behavioral/name_value_pair.h"

namespace character
{
  class attribute : public model::name_value_pair
  {
  public:
    attribute(QString name);
    attribute(QString name, int value);

    QString get_value() const override;
    QString get_name() const override;

    operator int() const;
    operator QString() const;

  private:
    int _value;
    QString _name;
  };
}
