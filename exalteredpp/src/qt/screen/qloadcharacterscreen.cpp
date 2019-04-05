#include "screen/qloadcharacterscreen.h"
#include "layout/qborderlayout.h"
#include "label/interfacelabels.h"
#include "filesystem_db.h"
#include "characternotfoundexception.h"

#include <QGroupBox>
#include <QLabel>
#include <QPushButton>

using qt::layout::QBorderLayout;
using namespace qt::labels;

namespace qt {
  namespace screen {
    qloadcharacterscreen::qloadcharacterscreen(QSharedPointer<manager::character_manager> char_manager, QWidget* parent)
      : QWidget (parent),
        character_manager(char_manager)
    {
      init();
    }

    void qloadcharacterscreen::enable_load_button()
    {
      load_character_button->setEnabled(true);
    }

    void qloadcharacterscreen::init()
    {
      load_character_button = new QPushButton(this);
      load_character_button->setText(LOAD_LABEL);
      load_character_button->setEnabled(false);
      connect(load_character_button, &QPushButton::clicked, this, &qloadcharacterscreen::load_character);

      QBorderLayout* layout = new QBorderLayout();
      layout->addWidget(load_character_button, QBorderLayout::South);

      QGroupBox* character_selection_group = new QGroupBox(this);
      QVBoxLayout* vertical_layout = new QVBoxLayout;
      for (auto char_pair: character_manager->characters())
        {
          QRadioButton *character_name_button = new QRadioButton(this);
          character_name_button->setText(char_pair.second);
          connect(character_name_button, &QRadioButton::click, this, &qloadcharacterscreen::enable_load_button);
          vertical_layout->addWidget(character_name_button);
          character_buttons.push_back(QPair<QRadioButton*, QString>(character_name_button, char_pair.first));
        }
      character_selection_group->setLayout(vertical_layout);
      layout->addWidget(character_selection_group, QBorderLayout::Center);

      this->setLayout(layout);
    }

    QString qloadcharacterscreen::detect_selected_character_id() const
    {
      for (auto char_button: character_buttons)
        {
          if (char_button.first->isChecked())
            return char_button.second;
        }
      return "";
    }

    void qloadcharacterscreen::load_character()
    {
      QString character_id = detect_selected_character_id();
      qDebug("Load character with id %s", qUtf8Printable(character_id));
      emit character_loaded(character_manager->load_character(character_id));
    }
  }
}
