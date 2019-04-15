#pragma once

#include "ability.h"
#include "ability_names.h"
#include "specialisation.h"
#include "serialisable.h"

namespace character
{
  class ability_group : public serialisable
  {
  public:

    ability_group() = default;

    ability_group(const QString& name, ability_names::ability_category category,
                  QList<ability> abilities = { ability(ability_names::ability_declination::NO_DECLINATION) },
                  QList<specialisation> specialisations = {});

    QString get_name() const;
    ability get_ability(const QString& name = ability_names::ability_declination::NO_DECLINATION) const;
    specialisation get_specialisation(const QString& name) const;
    ability_names::ability_category get_category() const;

    QList<ability> get_abilities() const;
    QList<specialisation> get_specialisations() const;

    bool has_ability(const QString& ability_name) const;
    bool has_specialisation(const QString& specialisation_name) const;

    void add_ability(ability new_ability);
    void add_ability(const QString& new_ability_name, unsigned int new_ability_value = 0);
    void set_ability_value(const QString& ability_name, unsigned int new_value);
    void increase_ability_value(const QString& ability_name, unsigned int add_value = 1);

    void add_specialisation(specialisation new_specialisation);
    void add_specialisation(const QString& new_specialisation_name, unsigned int initial_value = 1);
    void set_specialisation_value(const QString& specialisation_name, unsigned int new_value);
    void increase_specialisation_value(const QString& specialisation_name, unsigned int add_value = 1);
    void remove_specialisation(const QString& specialisation_to_remove);

    bool has_abilities() const;

    // serialisable interface
    void read_from_json(const QJsonObject &json);
    void write_to_json(QJsonObject &json) const;

    virtual ~ability_group() = default;

  private:
    QString group_name;
    QList<ability> actual_abilities;
    QList<specialisation> specialisations;
    ability_names::ability_category category;

    bool can_manage_ability(const QString& ability_name) const;
    QList<ability>::iterator get_ability_reference(const QString& name);
    QList<specialisation>::iterator get_specialisation_reference(const QString& name);

  };
}

