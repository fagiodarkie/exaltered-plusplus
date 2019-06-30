#include "wizard/character_creation_wizard.h"

#include <QLabel>
#include <QStackedWidget>

namespace qt {
  namespace wizard {

    using character::character;
    using namespace character;

    character_creation_wizard::character_creation_wizard(QSharedPointer<manager::character_manager> manager, QWidget* parent)
      : QWidget (parent),
        character_model(::character::creation::character_type_model::SOLAR_EXALT),
        char_manager(manager)
    {
      name_page = new character_creation_name_type_page(this);
      connect(name_page, &character_creation_name_type_page::back_issued, this, &character_creation_wizard::fallback);
      connect(name_page, &character_creation_name_type_page::character_type_chosen, this, &character_creation_wizard::load_attributes_priority);

      attribute_priority_page = new attributes_priority_page(this);
      connect(attribute_priority_page, &attributes_priority_page::back_issued, this, &character_creation_wizard::fallback);
      connect(attribute_priority_page, &attributes_priority_page::attributes_chosen, this, &character_creation_wizard::load_attributes_values);

      attribute_points_page = new character_creation_attribute_points_page(this);
      connect(attribute_points_page, &character_creation_attribute_points_page::back_issued, this, &character_creation_wizard::fallback);
      connect(attribute_points_page, &character_creation_attribute_points_page::attribute_points_chosen, this, &character_creation_wizard::load_attribute_points);

      layout = new QStackedLayout;
      layout->addWidget(name_page);
      layout->addWidget(attribute_priority_page);
      layout->addWidget(attribute_points_page);

      setLayout(layout);
    }

    void character_creation_wizard::load_attributes_priority(const QString&  char_name, creation::character_type type)
    {
      new_character_type = type;
      character_name = char_name;
      character_model = creation::character_type_model::get_by_character_type(type);
      attribute_priority_page->set_attribute_values(static_cast<int>(character_model.primary_category_attribute_value),
                                                    static_cast<int>(character_model.secondary_category_attribute_value),
                                                    static_cast<int>(character_model.tertiary_category_attribute_value));

      advance();
    }

    void character_creation_wizard::load_attributes_values(const QString& primary_attribute, const QString& secondary_attribute, const QString& tertiary_attribute)
    {
      points_per_category.clear();
      points_per_category.insert(attribute_names::ATTRIBUTE_CATEGORY_BY_NAME(primary_attribute), character_model.primary_category_attribute_value);
      points_per_category.insert(attribute_names::ATTRIBUTE_CATEGORY_BY_NAME(secondary_attribute), character_model.secondary_category_attribute_value);
      points_per_category.insert(attribute_names::ATTRIBUTE_CATEGORY_BY_NAME(tertiary_attribute), character_model.tertiary_category_attribute_value);

      attribute_points_page->set_total_points(points_per_category);

      advance();
    }

    void character_creation_wizard::load_attribute_points(const class attributes &points)
    {
      attributes = points;
      advance();
    }

    void character_creation_wizard::advance()
    {
      if (layout->currentIndex() + 1 < layout->count() )
        layout->setCurrentIndex(layout->currentIndex() + 1);
      else
        {
          QSharedPointer<character> final_character = char_manager->create_character(character_name,
                              new_character_type,
                              caste,
                              attributes,
                              abilities,
                              character_virtues,
                              power);
          emit character_created(final_character);
        }
    }

    void character_creation_wizard::fallback()
    {
      if (layout->currentIndex() > 0)
        layout->setCurrentIndex(layout->currentIndex() -1);
      else
        emit back_issued();
    }
  }
}
