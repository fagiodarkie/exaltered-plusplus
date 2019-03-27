#include "screen/qloadcharacterscreen.h"
#include "layout/qborderlayout.h"
#include "label/interfacelabels.h"
#include "filesystem_db.h"
#include "characternotfoundexception.h"

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
      init_load_button();
    }

    void qloadcharacterscreen::init_load_button()
    {
      QPushButton* loadButton = new QPushButton(this);
      loadButton->setText(LOAD_LABEL);
      connect(loadButton, &QPushButton::clicked, this, &qloadcharacterscreen::load_character);
      QBorderLayout* layout = new QBorderLayout();
      layout->addWidget(loadButton, QBorderLayout::South);
      this->setLayout(layout);
    }

    void qloadcharacterscreen::load_character()
    {
      qDebug("Load character");
      emit character_loaded(character_manager->load_character());
    }
  }
}
