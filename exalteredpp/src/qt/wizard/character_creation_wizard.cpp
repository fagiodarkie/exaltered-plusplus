#include "wizard/character_creation_wizard.h"

#include "wizard/character_creation_name_type_page.h"

namespace qt {
  namespace wizard {
    character_creation_wizard::character_creation_wizard(QWidget* parent)
      : QWizard (parent)
    {
      addPage(new character_creation_name_type_page(this));
    }

    void character_creation_wizard::accept()
    {

    }
  }
}
