#pragma once

#include <QWidget>
#include "widget/with_next_continue_buttons.h"
#include "widget/with_progress_bar.h"

namespace qt {
  namespace wizard {
    class provide_balance_details_page : public QWidget, public widget::with_progress_bar, public widget::with_next_back_buttons
    {
    public:
      provide_balance_details_page();
    };
  }
}

