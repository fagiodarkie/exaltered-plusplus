#pragma once

#include <QWidget>
#include "widget/with_next_continue_buttons.h"
#include "widget/with_progress_bar.h"

#include <QLabel>
#include "combat/physical_attack.h"

namespace qt {
  namespace wizard {
    class attack_result_page : public QWidget, public widget::with_progress_bar, public widget::with_next_back_buttons
    {
      Q_OBJECT
    public:
      explicit attack_result_page(QWidget *parent = nullptr);

      void with_outcome(std::shared_ptr<combat::outcome> attack_outcome);

    private:
      QLabel *result;
    };
}
}
