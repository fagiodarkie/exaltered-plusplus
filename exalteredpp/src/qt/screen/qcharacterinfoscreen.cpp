#include "screen/qcharacterinfoscreen.h"

#include <layout/qborderlayout.h>
#include "label/interfacelabels.h"
#include <QLabel>

namespace qt
{
  using namespace layout;

  namespace screen
  {
    qcharacterinfoscreen::qcharacterinfoscreen(std::shared_ptr<character::character> character, manager::character_manager &ch_manager, QWidget *parent)
      : QWidget(parent),
        character(character),
        character_manager(ch_manager)
    {
      QBorderLayout* outerLayout = new QBorderLayout();

      character_name_widget = new QLineEdit(character->get_name().c_str());
      save_button = new QPushButton(labels::SAVE_LABEL);

      QVBoxLayout *character_info_layout = new QVBoxLayout;
      character_info_layout->addWidget(character_name_widget);
      character_info_layout->addWidget(new QLabel(
            labels::info_labels::CHARACTER_TYPE_DESCRIPTION(
                    character::creation::CHARACTER_TYPE_NAMES.at(character->get_type()).c_str(),
                    character::exalt::exalt_caste::NAME_OF_CASTE.at(character->caste()).c_str())
      ));

      QWidget* character_info_widget = new QWidget;
      character_info_widget->setLayout(character_info_layout);

      outerLayout->addWidget(character_info_widget,  QBorderLayout::North);
      outerLayout->addWidget(save_button,            QBorderLayout::South);

      save_button->setEnabled(false);
      connect(character_name_widget, &QLineEdit::textEdited, this, &qcharacterinfoscreen::on_text_change);
      connect(save_button, &QPushButton::clicked, this, &qcharacterinfoscreen::save_character);

      setLayout(outerLayout);
    }

    void qcharacterinfoscreen::on_text_change(const QString& new_character_name)
    {
      save_button->setEnabled(new_character_name.toStdString() != character->get_name());
    }

    void qcharacterinfoscreen::save_character()
    {
      QString new_name = character_name_widget->text();
      character->set_name(new_name.toStdString());
      character_manager.save_character(character);
      save_button->setEnabled(false);
    }
  }
}
