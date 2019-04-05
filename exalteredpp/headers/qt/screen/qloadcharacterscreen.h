#pragma once

#include <QWidget>
#include <QRadioButton>
#include <QPushButton>
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
        void enable_load_button();
        void create_new_character();

    signals:
        void character_loaded(QSharedPointer<character::character> character);

    private:
        void init();

        QList<QPair<QRadioButton*, QString>> character_buttons;
        QPushButton *load_character_button, *new_character_button;
        QSharedPointer<manager::character_manager> character_manager;

        QString detect_selected_character_id() const;
        QWidget* create_lower_buttons();
        QWidget* load_character_buttons();
    };
  }
}
