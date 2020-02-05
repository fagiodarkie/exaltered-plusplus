#pragma once

#include <QLabel>
#include <QSpinBox>
#include <QWidget>
#include "widget/with_next_continue_buttons.h"
#include "widget/with_progress_bar.h"

#include "combat/attack_defines.h"

namespace qt {
  namespace wizard {
    class provide_balance_details_page : public QWidget, public widget::with_progress_bar, public widget::with_next_back_buttons
    {
      Q_OBJECT

    public:
      provide_balance_details_page();

      void remind_chosen_vd(combat::target_vd vd);

    signals:
      void balance_chosen(unsigned int balance);

    private:
      QSpinBox *balance_spin;
      QLabel *status_label;
    };
  }
}

