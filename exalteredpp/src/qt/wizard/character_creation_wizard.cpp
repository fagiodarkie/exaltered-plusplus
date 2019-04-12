#include "wizard/character_creation_wizard.h"

#include "wizard/character_creation_name_type_page.h"
#include <QStackedLayout>

namespace qt {
  namespace wizard {
    character_creation_wizard::character_creation_wizard(QSharedPointer<character::character> newly_created_character,
                                                         QWidget* parent)
      : final_character(newly_created_character), QWidget (parent)
    {
      QStackedLayout *stacked_layout = new QStackedLayout;
      stacked_layout->addWidget(new character_creation_name_type_page(this));

      setLayout(stacked_layout);
    }

  }
}
