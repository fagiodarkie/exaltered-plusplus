#pragma once

#include <QString>

namespace character
{
  class attribute
  {
  public:
    operator int() const;

    operator QString() const;

    attribute(QString name);

    attribute(QString name, int value);

  private:
    int _value;
    QString _name;
  };
}
