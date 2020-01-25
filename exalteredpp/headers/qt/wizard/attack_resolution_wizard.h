#pragma once

#include <QWidget>
#include <QStackedLayout>
#include "combat/physical_attack.h"

namespace qt { namespace wizard {

class attack_resolution_wizard : public QWidget
{
public:
  attack_resolution_wizard(std::shared_ptr<character::character> character,
                           std::shared_ptr<calculator::worker::abstract_calculator_worker> worker,
                           std::shared_ptr<dice::abstract_dice_roller> dice_roller,
                           QWidget* parent = nullptr);

signals:
  void outcome(combat::outcome attack_outcome);
  void back_issued();

private:
  void advance();
  void fallback();

  /*void load_attributes_priority(const QString&  char_name, character_type type, character::exalt::caste selected_caste);
  void load_attributes_values(const QString& primary_attribute, const QString& secondary_attribute, const QString& tertiary_attribute);
  void load_attribute_points(const attribute::attributes& points);
  void load_ability_values(const ability::abilities& abilities);
  void load_virtues(const virtues::virtues& virtues);
  void load_persona(const character::social::persona& persona);*/


  std::shared_ptr<character::character> _attacker;
  std::shared_ptr<calculator::worker::abstract_calculator_worker> _worker;
  std::shared_ptr<dice::abstract_dice_roller> _dice_roller;

  QStackedLayout *layout;
};

}}
