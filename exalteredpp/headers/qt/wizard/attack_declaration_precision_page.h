#pragma once

#include <QWidget>
#include "widget/with_next_continue_buttons.h"
#include "widget/with_progress_bar.h"
#include "widget/with_next_continue_buttons.h"
#include "widget/with_progress_bar.h"

namespace qt {
  namespace wizard {

    class attack_declaration_precision_page : public QWidget, public widget::with_progress_bar, public widget::with_next_back_buttons
    {
      Q_OBJECT
    public:
      explicit attack_declaration_precision_page(QWidget *parent = nullptr);

    signals:

    public slots:
    };

}
}
