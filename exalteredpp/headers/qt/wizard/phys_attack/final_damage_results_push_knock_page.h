#pragma once

#include <QCheckBox>
#include <QLabel>
#include <QRadioButton>
#include <QSpinBox>
#include <QWidget>
#include "widget/with_next_continue_buttons.h"
#include "widget/with_progress_bar.h"

namespace qt {
  namespace wizard {

    class final_damage_results_push_knock_page : public QWidget, public widget::with_progress_bar, public widget::with_next_back_buttons
    {
      Q_OBJECT
    public:
      explicit final_damage_results_push_knock_page(QWidget *parent = nullptr);

      void set_final_damage_stats(unsigned int final_damage_rolled, unsigned int final_damage_pool);

    signals:
      void knockdown(unsigned int devoted_successes);
      void knockback(unsigned int devoted_successes);
      void no_knocking();

    private:
      QRadioButton *knockdown_radio, *knockback_radio;
      QCheckBox *knock_him;
      QLabel *status_label;
      QSpinBox *push_meters_spin;

      void knock_toggled(int new_toggle_state);

      void knock_chosen();
    };
  }
}
