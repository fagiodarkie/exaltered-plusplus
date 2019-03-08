#pragma once

#include <string>
#include "character/attributes/attributes.h"
#include "serialisation/serialisable.h"

namespace character
{
  class character : public serialisable
  {
    public:
      // constructors
      character(QString name);
      character(const QJsonObject& object);

      // character fields
      QString getName() const;
      attributes getAttributes() const;

      // serialisable fields
      void read(const QJsonObject& object) override;
      void write(QJsonObject& object) const override;

    private:
      QString _name;
      attributes _attributes;

    };
}
