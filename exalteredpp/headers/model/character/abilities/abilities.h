#pragma once

#include <QMap>
#include "serialisable.h"
#include "ability_names.h"
#include "ability.h"

namespace character
{
  class abilities : public QMap<ability_name, ability>, serialisable
  {

  public:
    void read_from_json(const QJsonObject &json) override;
    void write_to_json(QJsonObject &json) const override;

    virtual ~abilities() = default;
  };
}
