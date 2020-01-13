#ifndef CASTE_STYLE_H
#define CASTE_STYLE_H

#include <QString>
#include <QMap>
#include <QList>
#include "creation/character_type_model.h"
#include "../thirdparty/darkstyle/DarkStyle.h"

namespace qt {
  class style {

  public:
    static void SET_CASTE(character::creation::character_type caste);

    static void application(QApplication& app);

    static void foreground(QPushButton* button);
    static void forget(QPushButton* button);

  private:

    static const QMap<character::creation::character_type, QColor> MAIN_COLOR_OF_CASTE;
    static const QList<character::creation::character_type> LIGHT_TYPES ;

    static DarkStyle* STYLE;

    static QApplication *APP;

    //  { character::creation::TYPE_MORTAL_EXTRA,      qt::style::theme("b4b4ba", "949499", "1e1515", "423329") },
    //  { character::creation::TYPE_MORTAL_HERO,       qt::style::theme("b4b4ba", "949499", "1e1515", "aa7a49") },
    //  { character::creation::TYPE_TERRESTRIAL_EXALT, qt::style::theme("acaeb7", "83858c", "050607", "897c9b") }, // TO BE CHANGED
    //  { character::creation::TYPE_SOLAR_EXALT,       qt::style::theme("15161c", "050607", "acaeb7", "aa7a49") },
    //  { character::creation::TYPE_ABYSSAL_EXALT,     qt::style::theme("15161c", "050607", "acaeb7", "6d231f") },
    //  { character::creation::TYPE_INFERNAL_EXALT,    qt::style::theme("15161c", "050607", "acaeb7", "345e4a") }

  };
}


#endif // CASTE_STYLE_H
