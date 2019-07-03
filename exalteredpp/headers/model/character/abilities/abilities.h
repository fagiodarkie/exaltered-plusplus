#pragma once

#include <QMap>
#include "serialisable.h"
#include "ability_names.h"
#include "ability_group.h"

namespace character
{
  class abilities : public QMap<ability_names::ability_enum, ability_group>, serialisable
  {

  public:
    void read_from_json(const QJsonObject &json) override;
    void write_to_json(QJsonObject &json) const override;

    virtual ~abilities() = default;
  };
}
