#include "wizard/character_creation_wizard.h"

#include <QLabel>
#include <QStackedWidget>

namespace qt {
  namespace wizard {
    character_creation_wizard::character_creation_wizard(QSharedPointer<character::character> newly_created_character,
                                                         QWidget* parent)
      : QWidget (parent),
        character_model(character_type_model::SOLAR_EXALT),
        final_character(newly_created_character)
    {
      name_page = new character_creation_name_type_page(this);
      connect(name_page, &character_creation_name_type_page::back_issued, this, &character_creation_wizard::fallback);
      connect(name_page, &character_creation_name_type_page::character_type_chosen, this, &character_creation_wizard::load_attributes_priority);

      attribute_priority_page = new attributes_priority_page(this);
      connect(attribute_priority_page, &attributes_priority_page::back_issued, this, &character_creation_wizard::fallback);
      connect(attribute_priority_page, &attributes_priority_page::attributes_chosen, this, &character_creation_wizard::load_attributes_values);

      layout = new QStackedLayout;
      layout->addWidget(name_page);
      layout->addWidget(attribute_priority_page);

      setLayout(layout);
    }

    void character_creation_wizard::load_attributes_priority(QString char_name, character::creation::character_type type)
    {
      new_character_type = type;
      final_character->set_name(char_name);
      final_character->set_type(type);
      character_model = character::creation::character_type_model::get_by_character_type(type);
      attribute_priority_page->set_attribute_values(static_cast<int>(character_model.primary_category_attribute_value),
                                                    static_cast<int>(character_model.secondary_category_attribute_value),
                                                    static_cast<int>(character_model.tertiary_category_attribute_value));

      advance();
    }

    void character_creation_wizard::load_attributes_values(QString primary_attribute, QString secondary_attribute, QString tertiary_attribute)
    {

    }

    void character_creation_wizard::advance()
    {
      layout->setCurrentIndex(layout->currentIndex() + 1);
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
