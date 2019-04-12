#pragma once

#include <QWizard>

#include "creation/character_creation_configuration.h"
#include "creation/character_type_model.h"
#include "attributes/attributes.h"
#include "abilities/abilities.h"
#include "character.h"

#include "serialisation/db_abstraction.h"
#include "abilities/abstract_ability_factory.h"

namespace qt {
  namespace wizard {

    using namespace character::creation;

    class character_creation_wizard : public QWidget
    {
      Q_OBJECT
    public:
      character_creation_wizard(QSharedPointer<character::character> newly_created_character,
                                QWidget* parent = nullptr);

    signals:
      void character_created(QSharedPointer<character::character> new_character);

    private:
      character_type character_type;
      character_creation_configuration configuration;
      character::attributes attributes;
      character::abilities abilities;
      QSharedPointer<character::character> final_character;
    };
  }
}
