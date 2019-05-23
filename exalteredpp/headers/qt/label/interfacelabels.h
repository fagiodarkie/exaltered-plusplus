#pragma once

#include <QString>

namespace qt {
  namespace labels {
    static QString LOAD_LABEL     = "Load";
    static QString SAVE_LABEL     = "Save";
    static QString NEW_LABEL      = "New";
    static QString NEXT_LABEL     = "Next";
    static QString CANCEL_LABEL   = "Cancel";
    static QString APP_TITLE      = "Divine Games";

    namespace creation_wizard {
      static QString CHARACTER_NAME_LABEL = "Character name:";
      static QString CHARACTER_TYPE_LABEL = "Character type:";

      static QString PRIMARY_ATTRIBUTE    = "Primary Attribute";
      static QString SECONDARY_ATTRIBUTE  = "Secondary Attribute";
      static QString TERTIARY_ATTRIBUTE   = "Tertiary Attribute";

      static QString ATTRIBUTE_LABEL_WITH_TOTAL_POINTS(const QString& label, int points)
      {
        return QString("%1 (total points: %2)").arg(label, QString::number(points));
      }

      static QString ATTRIBUTE_WITH_POINTS(const QString& label, int points)
      {
        return QString("%1: (%2)").arg(label, QString::number(points));
      }
    }
  }
}
