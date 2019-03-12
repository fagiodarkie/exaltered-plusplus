#pragma once

#include <QWidget>

namespace screen {
  class QLoadCharacterScreen : public QWidget
  {
    Q_OBJECT

  public:
      QLoadCharacterScreen(QWidget* parent);

  private slots:
      void loadCharacter();
  };
}

