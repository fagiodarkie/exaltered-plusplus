#include "screen/qloadcharacterscreen.h"
#include "layout/qborderlayout.h"
#include "label/interfacelabels.h"
#include "filesystem_db.h"
#include "characternotfoundexception.h"
#include "caste_style.h"

#include <QGroupBox>
#include <QLabel>
#include <QPushButton>

using qt::layout::QBorderLayout;
using namespace qt::labels;

namespace qt {
  namespace screen {
    qloadcharacterscreen::qloadcharacterscreen(manager::character_manager& char_manager, QWidget* parent)
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
      QWidget* south_widget = create_lower_buttons();
      QBorderLayout* layout = new QBorderLayout();
      layout->addWidget(south_widget, QBorderLayout::South);

      QWidget* character_selection_group = load_character_buttons();
      layout->addWidget(character_selection_group, QBorderLayout::Center);

      this->setLayout(layout);
    }

    QWidget* qloadcharacterscreen::create_lower_buttons()
    {
      load_character_button = new QPushButton(this);
      load_character_button->setText(LOAD_LABEL);
      load_character_button->setEnabled(false);
      qt::style::foreground(load_character_button);
      connect(load_character_button, &QPushButton::clicked, this, &qloadcharacterscreen::load_character);

      new_character_button = new QPushButton(this);
      new_character_button->setText(NEW_LABEL);
      new_character_button->setEnabled(true);
      connect(new_character_button, &QPushButton::clicked, this, &qloadcharacterscreen::create_new_character);

      QVBoxLayout *buttons_layout = new QVBoxLayout(this);
      buttons_layout->addWidget(new_character_button);
      buttons_layout->addWidget(load_character_button);
      QWidget *south_widget = new QWidget(this);
      south_widget->setLayout(buttons_layout);

      return south_widget;
    }

    QWidget* qloadcharacterscreen::load_character_buttons()
    {
      QGroupBox* character_selection_group = new QGroupBox(this);
      QVBoxLayout* vertical_layout = new QVBoxLayout;
      for (auto char_pair: character_manager.characters())
        {
          QRadioButton *character_name_button = new QRadioButton(this);
          character_name_button->setText(char_pair.second.c_str());
          connect(character_name_button, &QRadioButton::clicked, this, &qloadcharacterscreen::enable_load_button);
          vertical_layout->addWidget(character_name_button);
          character_buttons.push_back(QPair<QRadioButton*, QString>(character_name_button, char_pair.first.c_str()));
        }

      vertical_layout->setAlignment(Qt::AlignTop);
      character_selection_group->setLayout(vertical_layout);
      return character_selection_group;
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

    void qloadcharacterscreen::create_new_character()
    {
      emit character_create_issued();
    }

    void qloadcharacterscreen::load_character()
    {
      QString character_id = detect_selected_character_id();
      qDebug("Load character with id %s", qUtf8Printable(character_id));
      emit character_loaded(character_manager.load_character(character_id.toStdString()));
    }
  }
}
