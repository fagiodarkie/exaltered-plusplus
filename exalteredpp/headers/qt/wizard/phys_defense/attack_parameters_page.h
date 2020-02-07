#ifndef ATTACK_PARAMETERS_PAGE_H
#define ATTACK_PARAMETERS_PAGE_H

#include "widget/with_next_continue_buttons.h"
#include "widget/with_progress_bar.h"

#include <QLabel>
#include <QSpinBox>
#include <QComboBox>

#include "combat/attack_defines.h"

namespace qt { namespace wizard {

    class attack_parameters_page : public QWidget, public widget::with_progress_bar, public widget::with_next_back_buttons
    {
      Q_OBJECT
    public:
      attack_parameters_page();

    signals:
      void attack_parameters(combat::body_target target, combat::damage_type_enum damage_type,
                          unsigned int precision_roll_result, unsigned int base_damage, unsigned int min_damage, unsigned int drill);


    private:
      QSpinBox *base_damage_box, *precision_result_box, *min_damage_box, *drill_box;
      QComboBox *damage_type_box, *body_target_box;
    };

}
}

#endif // ATTACK_PARAMETERS_PAGE_H
