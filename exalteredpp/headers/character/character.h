#pragma once

#include <string>
#include "character/attributes/attributes.h"
#include "serialisation/serialisable.h"

namespace character
{
  class character : public serialisable
  {
    public:
      // character fields
      character(QString name);

      QString getName() const;
      attributes getAttributes() const;

      // serialisable fields
      void read(QJsonObject& object) override;
      void write(QJsonObject& object) const override;

  protected:
      //virtual ~character() override = default;

    private:
      QString _name;
      attributes _attributes;

    };
}
