#include "screen/qcharacterinfoscreen.h"

#include <layout/qborderlayout.h>
#include "label/interfacelabels.h"

namespace qt
{
  using namespace layout;

  namespace screen
  {
    qcharacterinfoscreen::qcharacterinfoscreen(std::shared_ptr<character::character> character, manager::character_manager &ch_manager, QWidget *parent)
      : QWidget(parent),
        character(character),
        character_manager(ch_manager),
        character_name_widget(character->get_name().c_str()),
        save_button(labels::SAVE_LABEL)
    {
      QBorderLayout* outerLayout = new QBorderLayout();
      outerLayout->addWidget(&character_name_widget,  QBorderLayout::North);
      outerLayout->addWidget(&save_button,            QBorderLayout::South);

      save_button.setEnabled(false);
      connect(&character_name_widget, &QLineEdit::textEdited, this, &qcharacterinfoscreen::on_text_change);
      connect(&save_button, &QPushButton::clicked, this, &qcharacterinfoscreen::save_character);

      setLayout(outerLayout);
    }

    void qcharacterinfoscreen::on_text_change(const QString& new_character_name)
    {
      save_button.setEnabled(new_character_name.toStdString() != character->get_name());
    }

    void qcharacterinfoscreen::save_character()
    {
      QString new_name = character_name_widget.text();
      character->set_name(new_name.toStdString());
      character_manager.save_character(character);
      save_button.setEnabled(false);
    }
  }
}
