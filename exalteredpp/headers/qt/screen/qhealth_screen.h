#ifndef QHEALTH_SCREEN_H
#define QHEALTH_SCREEN_H

#include <QWidget>
#include <QPushButton>
#include <QRadioButton>
#include <QSpinBox>
#include <QLabel>

#include "character.h"
#include "managers/character_manager.h"

namespace qt { namespace screen {

    class qhealth_screen : public QWidget
    {
      Q_OBJECT
    public:
      qhealth_screen(std::shared_ptr<character::character> character,
      std::shared_ptr<manager::character_manager> manager,
      QWidget *parent = nullptr);

    private:
      std::shared_ptr<character::character> _character;
      std::shared_ptr<manager::character_manager> _manager;

      QPushButton *deal_heal_button;
      QRadioButton *deal_radio, *heal_radio;
      QSpinBox *_amount_box;
      QLabel *_summary_label;

      void on_deal_heal_switched();
      void on_deal_heal_issued();
      void heal_issued();
      void deal_issued();
    };
}}
#endif // QHEALTH_SCREEN_H
