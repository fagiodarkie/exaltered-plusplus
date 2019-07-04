#pragma once

#include "behavioral/name_value_pair.h"
#include "serialisable.h"

namespace character
{

  class ability : public model::name_value_pair, public serialisable
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

    void read_from_json(const QJsonObject &json) override;
    void write_to_json(QJsonObject &json) const override;

    bool operator==(const ability& other) const;

  private:
    QString _name;
    unsigned int _value;
  };

}
