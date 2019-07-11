#pragma once

#include <QString>
#include "serialisable.h"
#include "behavioral/name_value_pair.h"

namespace character {
  class specialisation : public model::name_value_pair, public serialisable
  {
  public:
    specialisation(const QString& name, unsigned int initial_value = 1);
    specialisation(const specialisation& o);
    specialisation& operator=(const specialisation& o);

    QString get_name() const override;
    QString get_value() const override;
    unsigned int get_specialisation_value() const;

    void set_value(unsigned int new_value);

    void read_from_json(const QJsonObject &json) override;
    void write_to_json(QJsonObject &json) const override;

    bool operator==(const specialisation& other) const;

  private:
    QString name;
    unsigned int value;

  };
}
