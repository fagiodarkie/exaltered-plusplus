#pragma once

#include <QWizardPage>
#include <QLineEdit>
#include <QComboBox>

#include "creation/character_type_model.h"

namespace qt {
  namespace wizard {

    using character::creation::character_type;

    class character_creation_name_type_page : public QWidget
    {
      Q_OBJECT

    public:
      character_creation_name_type_page(QWidget *parent = nullptr);

    signals:
      void character_type_chosen(const QString& character_name, character_type type);
      void back_issued();

    private:
      QLineEdit* character_name;
      QComboBox *combo_box;
      QPushButton *next_page, *cancel;

      void check_form();
      void chose_all();
    };
  }
}
