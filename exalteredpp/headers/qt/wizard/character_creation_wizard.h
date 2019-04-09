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

    class character_creation_wizard : public QWizard
    {
    public:
      character_creation_wizard(QWidget* parent = nullptr);

      void accept() override;

    private:
      character_type_model character_model;
      character_creation_configuration configuration;
      character::attributes attributes;
      character::abilities abilities;
      QSharedPointer<character::character> final_character;

      QSharedPointer<
    };
  }
}
