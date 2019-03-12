#pragma once

#include <QWidget>
#include <QPushButton>

namespace qt {
  namespace screen {
    class QLoadCharacterScreen : public QWidget
    {
      Q_OBJECT

    public:
        QLoadCharacterScreen(QWidget* parent);

    private slots:
//        void loadCharacter();

    private:
        void paint();
        void initLoadButton();

        QPushButton* loadButton;
    };
  }


}
