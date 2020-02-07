#ifndef FINAL_DAMAGE_INPUT_PAGE_H
#define FINAL_DAMAGE_INPUT_PAGE_H

#include <QWidget>

#include "widget/with_next_continue_buttons.h"
#include "widget/with_progress_bar.h"

#include <QRadioButton>
#include <QSpinBox>
#include <QLabel>

namespace qt { namespace wizard {

    class final_damage_input_page : public QWidget, public widget::with_progress_bar, public widget::with_next_back_buttons
    {
      Q_OBJECT
    public:
      explicit final_damage_input_page(QWidget *parent = nullptr);

      void set_final_damage_pool(unsigned int post_soak_pool);

    signals:
      void roll_damage();
      void with_damage(unsigned int damage);

    private:
      QRadioButton *roll_damage_radio, *provide_damage_radio;
      QSpinBox* provided_damage_box;
      QLabel *status;

      void on_submit();
      void on_radio_change();
    };
}}
#endif // FINAL_DAMAGE_INPUT_PAGE_H
