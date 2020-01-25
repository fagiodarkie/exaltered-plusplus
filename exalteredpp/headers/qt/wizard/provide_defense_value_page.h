#pragma once

#include <QWidget>
#include "widget/with_next_continue_buttons.h"
#include "widget/with_progress_bar.h"

namespace qt {
  namespace wizard {

    class provide_defense_value_page : public QWidget, public widget::with_progress_bar, public widget::with_next_back_buttons
    {
      Q_OBJECT
    public:
      explicit provide_defense_value_page(QWidget *parent = nullptr);

    signals:

    public slots:
    };
}
}
