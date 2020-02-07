#pragma once

#include <QStackedLayout>
#include <QWizard>
#include <QMap>
#include "qt/layout/qborderlayout.h"

#include "creation/character_creation_configuration.h"
#include "character.h"
#include "managers/character_manager.h"
#include "calculator/worker/abstract_calculator_worker.h"

#include "wizard/chargen/character_creation_name_type_page.h"
#include "wizard/chargen/attributes_priority_page.h"
#include "wizard/chargen/character_creation_ability_values.h"
#include "wizard/chargen/character_creation_attribute_points_page.h"
#include "wizard/chargen/character_creation_virtues_vice.h"
#include "wizard/chargen/character_creation_persona.h"

namespace qt {
  namespace wizard {

    class character_creation_wizard : public QWidget
    {
      Q_OBJECT
    public:
      character_creation_wizard(manager::character_manager &manager, calculator::worker::abstract_calculator_worker& worker, QWidget* parent = nullptr);

    signals:
      void character_created(std::shared_ptr<character::character> new_character);
      void back_issued();

    private:
      void advance();
      void fallback();
      void load_attributes_priority(const QString&  char_name, character_type type, character::exalt::caste selected_caste);
      void load_attributes_values(const QString& primary_attribute, const QString& secondary_attribute, const QString& tertiary_attribute);
      void load_attribute_points(const attribute::attributes& points);
      void load_ability_values(const ability::abilities& abilities);
      void load_virtues(const virtues::virtues& virtues);
      void load_persona(const character::social::persona& persona);


      QString                                               character_name;
      character_type                                        new_character_type;
      character::creation::character_type_model             character_model;
      character::creation::character_creation_configuration configuration;
      character::exalt::caste                               caste;
      ::virtues::virtues                                    character_virtues;
      attribute::attributes                                 attributes;
      ability::abilities                                    abilities;
      QMap<attribute::attribute_category, unsigned int>     points_per_category;
      power::essence                                        essence;
      power::willpower                                      willpower;
      power::health                                         health;
      power::logos                                          logos;
      character::social::persona                            persona;

      manager::character_manager&                     char_manager;
      calculator::worker::abstract_calculator_worker& calculator;

      character_creation_name_type_page*            name_page;
      attributes_priority_page*                     attribute_priority_page;
      character_creation_attribute_points_page*     attribute_points_page;
      character_creation_ability_values*            abilities_page;
      character_creation_virtues_vice*              virtues_page;
      character_creation_persona*                   persona_page;

      QStackedLayout *layout;
    };
  }
}
