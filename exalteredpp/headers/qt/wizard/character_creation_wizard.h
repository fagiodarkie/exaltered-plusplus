#pragma once

#include <QWizard>

#include "creation/character_creation_configuration.h"
#include "creation/character_type_model.h"
#include "attributes/attributes.h"
#include "abilities/abilities.h"
#include "character.h"

#include "wizard/character_creation_name_type_page.h"

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
      void back_issued();

    private:
      void load_attributes_priority(QString char_name, character_type type);


      character_type new_character_type;
      character_type_model character_model;
      character_creation_configuration configuration;
      character::attributes attributes;
      character::abilities abilities;
      QSharedPointer<character::character> final_character;

      character_creation_name_type_page* name_page;

    };
  }
}
