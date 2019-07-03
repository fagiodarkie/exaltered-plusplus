#pragma once

#include <QStackedLayout>
#include <QWizard>

#include "creation/character_creation_configuration.h"
#include "creation/character_type_model.h"
#include "character.h"

#include "managers/character_manager.h"
#include "qt/layout/qborderlayout.h"

#include "wizard/character_creation_name_type_page.h"
#include "wizard/attributes_priority_page.h"
#include "wizard/character_creation_favorite_abilities.h"
#include "wizard/character_creation_attribute_points_page.h"
#include "wizard/character_creation_virtues_vice.h"

namespace qt {
  namespace wizard {

    class character_creation_wizard : public QWidget
    {
      Q_OBJECT
    public:
      character_creation_wizard(QSharedPointer<manager::character_manager> manager, QWidget* parent = nullptr);

    signals:
      void character_created(QSharedPointer<character::character> new_character);
      void back_issued();

    private:
      void advance();
      void fallback();
      void load_attributes_priority(const QString&  char_name, character_type type, character::exalt::caste selected_caste);
      void load_attributes_values(const QString& primary_attribute, const QString& secondary_attribute, const QString& tertiary_attribute);
      void load_attribute_points(const character::attributes& points);
      void load_favored_abilities(const QList<character::ability_names::ability_enum>& favored_abilities);
      void load_persona(const character::virtues::virtues& virtues);


      QString character_name;
      character_type new_character_type;
      character::creation::character_type_model character_model;
      character::creation::character_creation_configuration configuration;
      character::exalt::caste caste;
      character::virtues::virtues character_virtues;
      character::attributes attributes;
      character::abilities abilities;
      QMap<character::attribute_names::attribute_category, unsigned int> points_per_category;
      character::power::power_container power;

      QSharedPointer<manager::character_manager> char_manager;

      character_creation_name_type_page* name_page;
      attributes_priority_page* attribute_priority_page;
      character_creation_attribute_points_page* attribute_points_page;
      character_creation_virtues_vice* virtues_page;
      character_creation_favorite_abilities* favorite_abilities_page;

      QStackedLayout *layout;
    };
  }
}
