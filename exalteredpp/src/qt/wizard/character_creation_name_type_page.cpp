#include "wizard/character_creation_name_type_page.h"

#include <QFormLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include "layout/qborderlayout.h"

#include "qt/label/interfacelabels.h"

namespace qt {
  namespace wizard {

    using namespace qt::labels::creation_wizard;
    using namespace qt::labels;

    character_creation_name_type_page::character_creation_name_type_page(QWidget *parent)
      : QWidget (parent)
    {
      QFormLayout* form = new QFormLayout;

      form->addRow(new QLabel(CHARACTER_NAME_LABEL), new QLineEdit);

      combo_box = new QComboBox;
      for (auto type: character::creation::CHARACTER_TYPE_NAMES.keys())
        {
          combo_box->addItem(character::creation::CHARACTER_TYPE_NAMES[type]);
        }

      form->addRow(new QLabel(CHARACTER_TYPE_LABEL), combo_box);
      QWidget* central_widget = new QWidget;
      central_widget->setLayout(form);

      QHBoxLayout* buttons_layout = new QHBoxLayout;

      next_page = new QPushButton(NEXT_LABEL), cancel = new QPushButton(CANCEL_LABEL);
      next_page->setEnabled(false);
      connect(next_page, &QPushButton::clicked, this, &character_creation_name_type_page::chose_all);
      connect(cancel, &QPushButton::clicked, this, &character_creation_name_type_page::back_issued);

      QWidget* buttons = new QWidget;
      buttons->setLayout(buttons_layout);

      layout::QBorderLayout *outer_layout = new layout::QBorderLayout(this);
      outer_layout->addWidget(central_widget, layout::QBorderLayout::Center);
      outer_layout->addWidget(buttons, layout::QBorderLayout::South);
      setLayout(outer_layout);
    }

    void character_creation_name_type_page::chose_all()
    {
      QString char_name = character_name->text(),
          char_type = combo_box->currentText();
      for (auto type: character::creation::CHARACTER_TYPE_NAMES.keys())
        {
          if (character::creation::CHARACTER_TYPE_NAMES[type] == char_type)
            {
              emit character_type_chosen(char_name, type);
              break;
            }
        }
    }

    void character_creation_name_type_page::check_form()
    {
      QString char_name = character_name->text();
      next_page->setEnabled(!char_name.isEmpty());
    }
  }
}

