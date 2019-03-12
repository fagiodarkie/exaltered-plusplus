#include "screen/qloadcharacterscreen.h"
#include "layout/qborderlayout.h"
#include "label/interfacelabels.h"

#include <QLabel>

using qt::layout::QBorderLayout;
using namespace qt::labels;

namespace qt {
  namespace screen {
    QLoadCharacterScreen::QLoadCharacterScreen(QWidget* parent)
      : QWidget (parent)
    {
      initLoadButton();
      paint();
    }

    void QLoadCharacterScreen::initLoadButton()
    {
      loadButton = new QPushButton(this);
      loadButton->setText(LOAD_CHARACTER);
    }

    void QLoadCharacterScreen::paint()
    {
      QBorderLayout* layout = new QBorderLayout();
      layout->addWidget(loadButton, QBorderLayout::South);
      this->setLayout(layout);
    }
  }
}
