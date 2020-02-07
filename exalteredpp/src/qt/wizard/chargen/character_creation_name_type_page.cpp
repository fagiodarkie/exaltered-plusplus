#include "wizard/chargen/character_creation_name_type_page.h"

#include <QApplication>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include "layout/qborderlayout.h"
#include "common/reverse_search.h"
#include "caste_style.h"

#include "qt/label/interfacelabels.h"

namespace qt {
  namespace wizard {

    using namespace qt::labels::creation_wizard;
    using namespace qt::labels;

    character_creation_name_type_page::character_creation_name_type_page(QWidget *parent)
      : QWidget (parent)
    {
      QFormLayout* form = new QFormLayout;

      character_name = new QLineEdit;
      form->addRow(new QLabel(CHARACTER_NAME_LABEL), character_name);
      connect(character_name, &QLineEdit::textChanged, this, &character_creation_name_type_page::check_form);

      combo_box = new QComboBox;
      for (auto type: character::creation::CHARACTER_TYPE_LIST)
        {
          combo_box->addItem(character::creation::CHARACTER_TYPE_NAMES.at(type).c_str());
        }

      form->addRow(new QLabel(CHARACTER_TYPE_LABEL), combo_box);
      caste_combo_box = new QComboBox;
      caste_label = new QLabel(labels::creation_wizard::CASTE);
      form->addRow(caste_label, caste_combo_box);

      connect(combo_box, &QComboBox::currentTextChanged, this, &character_creation_name_type_page::hide_show_caste_box);
      QWidget* central_widget = new QWidget;
      central_widget->setLayout(form);

      on_next_issued([this]() { chose_all(); });

      layout::QBorderLayout *outer_layout = new layout::QBorderLayout;
      outer_layout->addWidget(_progress_bar, layout::QBorderLayout::North);
      outer_layout->addWidget(central_widget, layout::QBorderLayout::Center);
      outer_layout->addWidget(buttons_layout(), layout::QBorderLayout::South);

      setLayout(outer_layout);
      hide_show_caste_box();
    }

    void character_creation_name_type_page::hide_show_caste_box()
    {
      character_type selected_type = commons::reverse_search_in_map(character::creation::CHARACTER_TYPE_LIST,
                                                                    character::creation::CHARACTER_TYPE_NAMES,
                                                                    combo_box->currentText().toStdString());

      qt::style::SET_CASTE(selected_type);

      auto available_castes = character::exalt::exalt_caste::CASTES_OF_EXALT_TYPE.at(selected_type);
      if (available_castes.empty() || available_castes.size() == 1)
        {
          caste_combo_box->hide();
          caste_label -> hide();
          return;
        }

      caste_label->show();
      caste_combo_box->clear();
      for (character::exalt::caste available_caste : available_castes)
        {
          caste_combo_box->addItem(character::exalt::exalt_caste::get_caste(available_caste).name().c_str());
        }
      caste_combo_box->show();
    }

    void character_creation_name_type_page::chose_all()
    {
      QString char_name = character_name->text(),
          char_type = combo_box->currentText();

      character_type type = commons::reverse_search_in_map(character::creation::CHARACTER_TYPE_LIST, character::creation::CHARACTER_TYPE_NAMES, char_type.toStdString());
      character::exalt::caste caste_type = caste_combo_box->isHidden()
          ? character::exalt::caste::NO_CASTE
          : commons::reverse_search_in_map(character::exalt::exalt_caste::CASTES_OF_EXALT_TYPE.at(type),
              character::exalt::exalt_caste::NAME_OF_CASTE,
              caste_combo_box->currentText().toStdString());

      emit character_type_chosen(char_name, type, caste_type);
    }

    void character_creation_name_type_page::check_form()
    {
      QString char_name = character_name->text();
      enable_next(!char_name.isEmpty());
    }
  }
}

