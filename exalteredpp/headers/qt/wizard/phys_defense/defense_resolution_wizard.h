#ifndef HEADERSQTWIZARDPHYS_DEFENSEDEFENSE_RESOLUTION_WIZARD_H
#define HEADERSQTWIZARDPHYS_DEFENSEDEFENSE_RESOLUTION_WIZARD_H

#include <QStackedLayout>
#include <QWidget>

#include <wizard/phys_attack/attack_result_page.h>
#include <wizard/phys_attack/final_damage_results_push_knock_page.h>

#include "attack_parameters_page.h"
#include "character.h"
#include "defense_declaration_page.h"
#include "final_damage_input_page.h"
#include "combat/physical_attack.h"
#include "calculator/derived_value_calculator.h"

namespace qt { namespace wizard {

    class defense_resolution_wizard : public QWidget
    {
      Q_OBJECT
    public:
      explicit defense_resolution_wizard(std::shared_ptr<character::character> character,
                                         const calculator::derived_value_calculator& worker,
                                         QWidget* parent = nullptr);

    signals:
      void outcome(std::shared_ptr<combat::outcome> attack_outcome);
      void back_issued();

    private:

      void chosen_vd(combat::target_vd vd, int vd_modifier, bool will_counter);

      void with_precision(combat::body_target target, combat::damage_type_enum damage_type,
                          unsigned int successes, unsigned int base_damage, unsigned int min_damage, unsigned int drill);

      void with_final_damage(unsigned int final_damage);
      void roll_final_damage();

      void knockdown(unsigned int devoted_successes);
      void knockback(unsigned int devoted_successes);
      void no_knocking();

      void advance();
      void advance_to_result();

      defense_declaration_page *defense_declaration;
      attack_parameters_page  *attack_parameters;
      final_damage_input_page *final_damage_input;
      final_damage_results_push_knock_page *final_damage;
      attack_result_page *result_page;

      std::shared_ptr<character::character> _defender;
      calculator::derived_value_calculator _worker;
      std::shared_ptr<combat::combat_step> _step;
      std::shared_ptr<combat::outcome> _outcome;
      bool _chose_to_counter;

      template<typename T>
      typename std::enable_if<std::is_base_of<combat::combat_step, T>::value, std::shared_ptr<T>>::type
      step_as()
      {
        return std::dynamic_pointer_cast<T>(_step);
      }

      QStackedLayout *layout;
    };
}
}

#endif // HEADERSQTWIZARDPHYS_DEFENSEDEFENSE_RESOLUTION_WIZARD_H
