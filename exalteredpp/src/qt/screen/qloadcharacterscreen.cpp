#include "screen/qloadcharacterscreen.h"
#include "layout/qborderlayout.h"
#include "label/interfacelabels.h"
#include "filesystem_db.h"
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
      serialisation::filesystem_db fsdb;
      qDebug("Load character");
      try
      {
        QSharedPointer<character::character> loaded_character = fsdb.load_character("test");
        emit character_loaded(loaded_character);
      }
      catch (exception::character_not_found_exception* e)
      {
        qDebug(e->what());
        QSharedPointer<character::character> loaded_character(new character::character("test"));
        emit character_loaded(loaded_character);
      }
    }

    void qloadcharacterscreen::paint()
    {
      QBorderLayout* layout = new QBorderLayout();
      layout->addWidget(loadButton, QBorderLayout::South);
      this->setLayout(layout);
    }
  }
}
