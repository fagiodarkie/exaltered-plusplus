#ifndef CASTE_STYLE_H
#define CASTE_STYLE_H

#include <QString>
#include <QMap>
#include <QFont>
#include "creation/character_type_model.h"

namespace qt { namespace style {
    struct theme {

      theme(QString&& _bg = "", QString&& _sh = "", QString&& _txt = "", QString&& _col = "")
        : background(_bg), shade(_sh), text(_txt), color(_col) { }

      QString background, shade, text, color;
    };

} }

static const QString STYLE = "QWidget { background-color: #%1; color: #%3; selection-background-color: #%2; }"
                             "QGroupBox { border: 2px inset #%4; padding: 4px; margin: 3px; } "
                             "QGroupBox::title { subcontrol-origin: margin; left: 10px; padding: 0 3px 0 3px; }"
                             "QVBoxLayout { border: 1px inset #%2; } "
                             "QScrollArea { border: 1px inset #%2; } "
                             "QBorderLayout { border: 1px inset #%2; } "
                             "QTabWidget::pane { border: 1px inset #%2; } "
                             "QTabBar::tab { background-color: #%1; border: 2px inset #%2; } "
                             "QPushButton { background-color: #%2; color: #%4; border: 2px inset #%4; } "
                             "QPushButton:disabled { background-color: #%3; color: #%2; border: 1px inset #%2; }"
                             "QPushButton:pressed { background-color: #%3; }"
                             "QSpinBox { border: 3 inset #%2; } "
                             "QLabel { border-width: 0px; } "
                             "QLineEdit { border: 1px inset #%2; background: #%2; } "
                             "QComboBox:disabled { border: 1px inset #%2 } "
                             "QProgressBar:horizontal { background: #%1 } "
                             "QProgressBar::chunk:horizontal { background: #%4 } "
                             "";


static const QMap<character::creation::character_type, qt::style::theme> THEME_OF_CASTE = {
  { character::creation::TYPE_MORTAL_EXTRA,      qt::style::theme("b4b4ba", "949499", "1e1515", "423329") },
  { character::creation::TYPE_MORTAL_HERO,       qt::style::theme("b4b4ba", "949499", "1e1515", "aa7a49") },
  { character::creation::TYPE_TERRESTRIAL_EXALT, qt::style::theme("acaeb7", "83858c", "050607", "897c9b") }, // TO BE CHANGED
  { character::creation::TYPE_SOLAR_EXALT,       qt::style::theme("15161c", "050607", "acaeb7", "aa7a49") },
  { character::creation::TYPE_ABYSSAL_EXALT,     qt::style::theme("15161c", "050607", "acaeb7", "6d231f") },
  { character::creation::TYPE_INFERNAL_EXALT,    qt::style::theme("15161c", "050607", "acaeb7", "345e4a") }
};

static QFont FONT("");

static const QString STYLE_OF(character::creation::character_type type)
{
  auto theme = THEME_OF_CASTE[type];
  return STYLE
      .arg(theme.background )
      .arg(theme.shade      )
      .arg(theme.text       )
      .arg(theme.color      );
}

#endif // CASTE_STYLE_H
