#include "caste_style.h"

namespace qt {

  DarkStyle* style::STYLE = nullptr;
  QApplication* style::APP = nullptr;

  const QList<character::creation::character_type> style::LIGHT_TYPES = {
    character::creation::TYPE_MORTAL_EXTRA,
    character::creation::TYPE_MORTAL_HERO,
    character::creation::TYPE_TERRESTRIAL_EXALT
  };

  const QMap<character::creation::character_type, QColor> style::MAIN_COLOR_OF_CASTE = {
     { character::creation::TYPE_MORTAL_EXTRA,      QColor(66, 51, 41)    },
     { character::creation::TYPE_MORTAL_HERO,       QColor(170, 122, 73)  },
     { character::creation::TYPE_TERRESTRIAL_EXALT, QColor(137, 124, 155) }, // TO BE CHANGED
     { character::creation::TYPE_SOLAR_EXALT,       QColor(170, 122, 73)  },
     { character::creation::TYPE_ABYSSAL_EXALT,     QColor(109, 35, 31)   },
     { character::creation::TYPE_INFERNAL_EXALT,    QColor(52, 94, 74)    }
   };

  void style::foreground(QPushButton *button)
  {
    if (button == nullptr)
      return;

    STYLE->foreground(button);
  }

  void style::forget(QPushButton *button)
  {
    STYLE->forget(button);
  }

  void style::SET_CASTE(character::creation::character_type caste)
  {
    if (!STYLE || !APP)
      return;

    auto color = MAIN_COLOR_OF_CASTE[caste];
    STYLE->setMainColor(color);
    STYLE->setDark(!LIGHT_TYPES.contains(caste));
    APP->setStyle(STYLE);
    auto palette = APP->palette();
    STYLE->polish(palette);
    APP->setPalette(palette);

  }

  void style::application(QApplication& app)
  {
    STYLE = new DarkStyle;
    APP = &app;
    app.setStyle(STYLE);
  }


}

