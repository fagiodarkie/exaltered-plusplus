#pragma once

#include <map>
#include "attribute_names.h"
#include "attribute.h"
#include "serialisable.h"

namespace character
{
  class attributes : public QMap<attribute_names::attribute, attribute>, serialisable
  {

  public:
    void read_from_json(const QJsonObject &json) override;
    void write_to_json(QJsonObject &json) const override;

    virtual ~attributes() = default;
  };
}

