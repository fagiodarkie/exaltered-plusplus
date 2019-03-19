#include "screen/qloadcharacterscreen.h"
#include "layout/qborderlayout.h"
#include "label/interfacelabels.h"
#include "filesystem_db.h"
#include "managers/character_manager.h"
#include "characternotfoundexception.h"

#include <QLabel>

using qt::layout::QBorderLayout;
using namespace qt::labels;

namespace qt {
  namespace screen {
    qloadcharacterscreen::qloadcharacterscreen(QWidget* parent)
      : QWidget (parent)
    {
      init_load_button();
      paint();
    }

    void qloadcharacterscreen::init_load_button()
    {
      loadButton = new QPushButton(this);
      loadButton->setText(LOAD_CHARACTER);
      connect(loadButton, &QPushButton::clicked, this, &qloadcharacterscreen::load_character);
    }

    void qloadcharacterscreen::load_character()
    {
      manager::character_manager char_manager(QSharedPointer<serialisation::db_abstraction>(new serialisation::filesystem_db()));

      qDebug("Load character");
      emit character_loaded(char_manager.load_character());
    }

    void qloadcharacterscreen::paint()
    {
      QBorderLayout* layout = new QBorderLayout();
      layout->addWidget(loadButton, QBorderLayout::South);
      this->setLayout(layout);
    }
  }
}
