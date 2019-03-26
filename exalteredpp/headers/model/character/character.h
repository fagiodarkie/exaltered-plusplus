#pragma once

#include <string>
#include <QObject>
#include "character/attributes/attributes.h"
#include "character/abilities/abilities.h"
#include "serialisation/serialisable.h"

namespace character
{
  class character : public QObject, public serialisable
  {
    Q_OBJECT

    public:
      // constructors
      character(QString name);
      character(const QJsonObject& object);

      // character fields
      QString get_name() const;
      void set_name(const QString& new_name);

      attribute get_attribute(attribute_name name) const;
      void set_attribute(attribute_name name, attribute attribute);

      ability get_ability(ability_name name) const;
      void set_ability(ability_name name, ability ability);

      // serialisable fields
      void read(const QJsonObject& object) override;
      void write(QJsonObject& object) const override;

  signals:
      void data_changed();

    private:
      QString _name;
      attributes _attributes;
      abilities _abilities;
    };
}
