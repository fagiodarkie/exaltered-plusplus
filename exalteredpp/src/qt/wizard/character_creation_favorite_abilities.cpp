#include "wizard/character_creation_favorite_abilities.h"

#include "label/interfacelabels.h"
#include "layout/qborderlayout.h"

namespace qt {
  namespace wizard {

    using namespace qt::labels::creation_wizard;
    using namespace qt::labels;

    character_creation_favorite_abilities::character_creation_favorite_abilities(QWidget *parent)
      : QWidget(parent)
    {

      QWidget* abilities = new QWidget;

      QHBoxLayout* buttons_layout = new QHBoxLayout;
      next_page = new QPushButton(NEXT_LABEL);
      cancel = new QPushButton(CANCEL_LABEL);
      buttons_layout->addWidget(cancel);
      buttons_layout->addWidget(next_page);

      next_page->setEnabled(false);
      connect(next_page, &QPushButton::clicked, this, &character_creation_favorite_abilities::next_issued);
      connect(cancel, &QPushButton::clicked, this, &character_creation_favorite_abilities::back_issued);

      QWidget* buttons = new QWidget;
      buttons->setLayout(buttons_layout);

      layout::QBorderLayout *outer_layout = new layout::QBorderLayout;
      outer_layout->addWidget(abilities, layout::QBorderLayout::Center);
      outer_layout->addWidget(buttons, layout::QBorderLayout::South);

      setLayout(outer_layout);
    }

    void character_creation_favorite_abilities::next_issued()
    {

    }

    QPushButton* character_creation_favorite_abilities::generate_button(character::ability_names::ability ability)
    {
      QPushButton* button = new QPushButton(character::ability_names::ABILITY_NAME[ability]);

      button->setCheckable(true);

      ability_of_button.insert(button, ability);
    }

  }
}
