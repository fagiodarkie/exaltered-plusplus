#pragma once

#include <QWidget>
#include <QPushButton>

#include <character.h>

namespace qt
{
  namespace screen
  {
    class qloadcharacterscreen : public QWidget
    {
      Q_OBJECT

    public:
        qloadcharacterscreen(QWidget* parent);

    private slots:
        void load_character();

    signals:
        void character_loaded(QSharedPointer<character::character> character);

    private:
        void paint();
        void init_load_button();

        QPushButton* loadButton;
    };
  }
}
