#pragma once

#include <QComboBox>
#include <QSpinBox>
#include <QLabel>
#include <QWidget>
#include "widget/with_next_continue_buttons.h"
#include "widget/with_progress_bar.h"

#include "combat/physical_attack.h"

namespace qt {
  namespace wizard {

    class provide_defense_value_page : public QWidget, public widget::with_progress_bar, public widget::with_next_back_buttons
    {
      Q_OBJECT
    public:
      explicit provide_defense_value_page(QWidget *parent = nullptr);

      void attack_properties(unsigned int precision_pool, int external_bonus, combat::damage_type_enum damage_type, combat::body_target target);

    signals:
      void defense_chosen(combat::target_vd vd, unsigned int vd_value,
                          unsigned int natural_soak, unsigned int armored_soak, unsigned int hardness);

    private:
      QComboBox *vd_selection_box;
      QSpinBox *vd_value_spin, *natural_soak_spin, *armored_soak_spin, *hardness_spin;
      QLabel* current_status;

      void on_defense_chosen();

    };
}
}
