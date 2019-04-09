#include "wizard/character_creation_name_type_page.h"

#include <QFormLayout>
#include <QLabel>
#include <QTextEdit>
#include <QComboBox>

namespace qt {
  namespace wizard {
    character_creation_name_type_page::character_creation_name_type_page(QWidget *parent)
      : QWizardPage (parent)
    {
      QFormLayout* form = new QFormLayout;

      form->addRow(new QLabel("Character name:"), new QTextEdit);
      QComboBox *combo_box = new QComboBox;
      combo_box->addItems({"Extra", "Hero", "Terrestrial Exalt", "Solar Exalt"});
      form->addRow(new QLabel("Character type:"), combo_box);

      setLayout(form);
    }
  }
}

