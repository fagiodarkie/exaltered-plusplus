#include "wizard/character_creation_wizard.h"

#include <QStackedLayout>

namespace qt {
  namespace wizard {
    character_creation_wizard::character_creation_wizard(QSharedPointer<character::character> newly_created_character,
                                                         QWidget* parent)
      : QWidget (parent),
        character_model(character_type_model::SOLAR_EXALT),
        final_character(newly_created_character)
    {
      name_page = new character_creation_name_type_page(this);
      connect(name_page, &character_creation_name_type_page::back_issued, this, &character_creation_wizard::back_issued);
      connect(name_page, &character_creation_name_type_page::character_type_chosen, this, &character_creation_wizard::load_attributes_priority);

      QStackedLayout *stacked_layout = new QStackedLayout;
      stacked_layout->addWidget(name_page);

      setLayout(stacked_layout);
    }

    void character_creation_wizard::load_attributes_priority(QString char_name, character::creation::character_type type)
    {
      new_character_type = type;
      final_character->set_name(char_name);
      final_character->set_type(type);
      character_model = character::creation::character_type_model::get_by_character_type(type);

      // load next screen;

    }
  }
}
