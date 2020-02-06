#ifndef FINAL_DAMAGE_INPUT_PAGE_H
#define FINAL_DAMAGE_INPUT_PAGE_H

#include <QWidget>

#include "widget/with_next_continue_buttons.h"
#include "widget/with_progress_bar.h"

namespace qt { namespace wizard {

    class final_damage_input_page : public QWidget, public widget::with_progress_bar, public widget::with_next_back_buttons
    {
      Q_OBJECT
    public:
      explicit final_damage_input_page(QWidget *parent = nullptr);

    signals:

    public slots:
    };
}}
#endif // FINAL_DAMAGE_INPUT_PAGE_H
