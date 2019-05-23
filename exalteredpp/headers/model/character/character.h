#pragma once

#include <string>
#include <QObject>
#include "character/attributes/attributes.h"
#include "character/abilities/abilities.h"
#include "serialisation/serialisable.h"
#include "creation/character_type_model.h"

namespace character
{
  using creation::character_type;

  class character : public QObject, public serialisable
  {
    Q_OBJECT

    public:
      // constructors
      character(QString name, unsigned int id = 0);
      character(const QJsonObject& object);

      // character fields
      QString get_name() const;
      void set_name(const QString& new_name);

      character_type get_type() const;
      void set_type(character_type type);

      attribute get_attribute(attribute_names::attribute name) const;
      void set_attribute(attribute_names::attribute name, attribute attribute);

      ability_group get_ability_group(ability_names::ability_name name) const;
      ability get_ability(ability_names::ability_name name, const QString& ability_declination = ability_names::ability_declination::NO_DECLINATION) const;
      void set_ability(ability_names::ability_name name, ability_group ability);

      // serialisable fields
      void read_from_json(const QJsonObject& object) override;
      void write_to_json(QJsonObject& object) const override;

      unsigned int id() const;

  signals:
      void data_changed();

    private:
      QString _name;
      character_type _type;
      unsigned int _id;
      attributes _attributes;
      abilities _abilities;
    };
}
