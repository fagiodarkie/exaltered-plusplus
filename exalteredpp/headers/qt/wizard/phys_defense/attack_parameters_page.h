#ifndef ATTACK_PARAMETERS_PAGE_H
#define ATTACK_PARAMETERS_PAGE_H

#include "widget/with_next_continue_buttons.h"
#include "widget/with_progress_bar.h"

namespace qt { namespace wizard {

    class attack_parameters_page : public QWidget, public widget::with_progress_bar, public widget::with_next_back_buttons
    {
      Q_OBJECT
    public:
      attack_parameters_page();
    };

}
}

#endif // ATTACK_PARAMETERS_PAGE_H
