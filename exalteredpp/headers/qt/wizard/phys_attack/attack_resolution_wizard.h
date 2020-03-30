#pragma once

#include <QWidget>
#include <QStackedLayout>
#include "combat/physical_attack.h"
#include "attack_declaration_precision_page.h"
#include "provide_defense_value_page.h"
#include "final_damage_results_push_knock_page.h"
#include "provide_balance_details_page.h"
#include "attack_result_page.h"

namespace qt { namespace wizard {

class attack_resolution_wizard : public QWidget
{
  Q_OBJECT
public:
  attack_resolution_wizard(std::shared_ptr<character::character> character,
                           const calculator::derived_value_calculator& worker,
                           QWidget* parent = nullptr);

signals:
  void outcome(std::shared_ptr<combat::outcome> attack_outcome);
  void back_issued();

private:
  void advance();
  void advance_to_result();
  void cancel();

  void attack_with(const equip::weapon& weapon, const std::vector<combat::attack_attribute>& attributes,
                   int internal_bonus, int external_bonus, combat::body_target target);

  void apply_defense_and_soak(combat::target_vd vd_type, unsigned int vd_value,
                              unsigned int natural_soak, unsigned int armored_soak, unsigned int hardness);

  void knockdown(unsigned int devoted_successes);
  void knockback(unsigned int devoted_successes);
  void no_knocking();

  void with_vd_balance(unsigned int balance);

  attack_declaration_precision_page *attack_declaration;
  provide_defense_value_page *defense_and_soak;
  final_damage_results_push_knock_page *final_damage;
  provide_balance_details_page *balance;
  attack_result_page *result_page;

  std::shared_ptr<character::character> _attacker;
  calculator::derived_value_calculator _worker;
  std::shared_ptr<dice::abstract_dice_roller> _dice_roller;
  std::shared_ptr<combat::combat_step> _step;
  std::shared_ptr<combat::outcome> _outcome;

  template<typename T>
  typename std::enable_if<std::is_base_of<combat::combat_step, T>::value, std::shared_ptr<T>>::type
  step_as()
  {
    return std::dynamic_pointer_cast<T>(_step);
  }

  QStackedLayout *layout;
};

}}
