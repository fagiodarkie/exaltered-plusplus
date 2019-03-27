#pragma once

#include <QWidget>

#include "managers/character_manager.h"
#include <character.h>

namespace qt
{
  namespace screen
  {
    class qloadcharacterscreen : public QWidget
    {
      Q_OBJECT

    public:
        qloadcharacterscreen(QSharedPointer<manager::character_manager> char_manager, QWidget* parent);

    private slots:
        void load_character();

    signals:
        void character_loaded(QSharedPointer<character::character> character);

    private:
        void paint();
        void init_load_button();

        QSharedPointer<manager::character_manager> character_manager;
    };
  }
}
