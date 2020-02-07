#ifndef DEFENSE_DECLARATION_PAGE_H
#define DEFENSE_DECLARATION_PAGE_H

#include <QCheckBox>
#include <QComboBox>
#include <QLabel>
#include <QSpinBox>
#include <QWidget>
#include <character.h>
#include "calculator/derived_value_calculator.h"
#include "widget/with_next_continue_buttons.h"
#include "widget/with_progress_bar.h"
#include "combat/attack_defines.h"

namespace qt { namespace wizard {

    class defense_declaration_page : public QWidget, public widget::with_progress_bar, public widget::with_next_back_buttons
    {
      Q_OBJECT
    public:
      explicit defense_declaration_page(std::shared_ptr<character::character> defender,
                                        const calculator::derived_value_calculator& calculator,
                                        QWidget *parent = nullptr);

    signals:
      void parry(int vd_modifier, const ability::ability_name& parry_ability, int weapon_defense, bool will_counter);
      void dodge(int vd_modifier);

    private:
      void on_submit();
      void refresh_vd();

      QComboBox *defense_box, *parry_ability_box;
      QLabel *defense_info_label;
      QCheckBox *counter_after_parry;
      QSpinBox *vd_value_modifier, *weapon_defense_box;
      std::shared_ptr<character::character> _defender;
      calculator::derived_value_calculator _calculator;
      bool _countering;
      unsigned int _vd_value;
    };

}}
#endif // DEFENSE_DECLARATION_PAGE_H
