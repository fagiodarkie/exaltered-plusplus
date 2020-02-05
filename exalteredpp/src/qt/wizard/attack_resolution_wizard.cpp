#include "wizard/attack_resolution_wizard.h"

namespace qt { namespace wizard {
    attack_resolution_wizard::attack_resolution_wizard(std::shared_ptr<character::character> character,
                                                       const calculator::derived_value_calculator& worker,
                                                       QWidget* parent)
      : QWidget(parent), _attacker(character), _worker(worker)
    {
      _step = std::make_shared<combat::attack_declaration>(combat::attack_declaration::declare().attacker(character));

      _dice_roller = std::make_shared<dice::dice_roller<>>();
      if (character::creation::character_type_model::get_by_character_type(character->type()).is_supernatural)
        _dice_roller = std::make_shared<dice::dice_roller<dice::no_brutal, dice::exalt_10_rule<>>>();

      attack_declaration = new attack_declaration_precision_page(_attacker);
      attack_declaration->on_back_issued([this]() { cancel(); });
      connect(attack_declaration, &attack_declaration_precision_page::attack_selected, this, &attack_resolution_wizard::attack_with);

      defense_and_soak = new provide_defense_value_page;
      defense_and_soak->disable_back();
      connect(defense_and_soak, &provide_defense_value_page::defense_chosen, this, &attack_resolution_wizard::apply_defense_and_soak);

      final_damage = new final_damage_results_push_knock_page;
      final_damage->disable_back();
      connect(final_damage, &final_damage_results_push_knock_page::knockback, this, &attack_resolution_wizard::knockback);
      connect(final_damage, &final_damage_results_push_knock_page::knockdown, this, &attack_resolution_wizard::knockdown);
      connect(final_damage, &final_damage_results_push_knock_page::no_knocking, this, &attack_resolution_wizard::no_knocking);

      balance = new provide_balance_details_page;
      balance->disable_back();
      connect(balance, &provide_balance_details_page::balance_chosen, this, &attack_resolution_wizard::with_vd_balance);

      result_page = new attack_result_page;
      result_page->disable_back();
      result_page->on_next_issued([this]() { advance(); });

      layout = new QStackedLayout;
      QList<QWidget*> pages = { attack_declaration, defense_and_soak, final_damage, balance, result_page };

      for (unsigned int i = 0; i < pages.size(); ++i)
        {
          layout->addWidget(pages.at(i));
          dynamic_cast<widget::with_progress_bar*>(pages.at(i))->set_progress_bar_status(i, pages.size());
        }
      layout->setCurrentIndex(0);

      setLayout(layout);
    }

    void attack_resolution_wizard::attack_with(const equip::weapon& weapon, const std::vector<combat::attack_attribute>& attributes,
                     unsigned int internal_bonus, unsigned int internal_malus,
                     unsigned int external_bonus, unsigned int external_malus, combat::body_target target)
    {
      if (target == combat::body_target::NO_TARGET)
        target = combat::body_part_roller().roll_body_part();

      _step = std::make_shared<combat::precision_roll>(step_as<combat::attack_declaration>()->with(weapon).is(attributes).roll_precision()
                                 .bonus(external_bonus).malus(external_malus)
                                 .internal_bonus(internal_bonus).internal_malus(internal_malus).target(target));

      auto pool = step_as<combat::precision_roll>()->pool();
      auto final_bonus = step_as<combat::precision_roll>()->external_bonus();

      defense_and_soak->attack_properties(pool, final_bonus, weapon.damage_type(), target);

      advance();
    }

    void attack_resolution_wizard::apply_defense_and_soak(combat::target_vd vd_type, unsigned int vd_value,
                                                          unsigned int natural_soak, unsigned int armored_soak, unsigned int hardness)
    {
      _step = std::make_shared<combat::vd_application>(step_as<combat::precision_roll>()->apply_and_defend(_dice_roller)
                                                      .defend_with_value(vd_type, vd_value));

      balance->remind_chosen_vd(vd_type);

      if (!step_as<combat::vd_application>()->hits())
        {
          _outcome = std::make_shared<combat::outcome>(step_as<combat::vd_application>()->on_fail());
        }
      else _step = std::make_shared<combat::raw_damage_and_position_computation>(step_as<combat::vd_application>()->on_success());

      if (!_outcome && !step_as<combat::raw_damage_and_position_computation>()->passes(natural_soak, armored_soak))
        {
          _outcome = std::make_shared<combat::outcome>(step_as<combat::raw_damage_and_position_computation>()->on_fail());
        }
      else _step = std::make_shared<combat::post_soak_damage>(step_as<combat::raw_damage_and_position_computation>()->on_pass(natural_soak, armored_soak));


      if (!_outcome && !step_as<combat::post_soak_damage>()->passes(hardness))
        {
          _outcome = std::make_shared<combat::outcome>(step_as<combat::post_soak_damage>()->on_fail());
        }
      else _step = std::make_shared<combat::post_hardness_damage>(step_as<combat::post_soak_damage>()->on_pass());

      if (!_outcome)
        {
          _step = std::make_shared<combat::final_damage>(step_as<combat::post_hardness_damage>()->roll(_dice_roller));

          auto final_damage_result = step_as<combat::final_damage>()->damage();
          auto damage_pool = step_as<combat::final_damage>()->attack_status()->post_soak_damage;
          final_damage->set_final_damage_stats(final_damage_result, damage_pool);

          advance();
        }
      else
        {
          advance_to_result();
        }

    }

    void attack_resolution_wizard::knockdown(unsigned int devoted_successes)
    {
      step_as<combat::final_damage>()->knockdown(devoted_successes);
      advance();
    }

    void attack_resolution_wizard::knockback(unsigned int devoted_successes)
    {
      step_as<combat::final_damage>()->knockback_meters(devoted_successes);
      advance();
    }

    void attack_resolution_wizard::no_knocking()
    {
      _outcome = std::make_shared<combat::outcome>(step_as<combat::final_damage>()->end_attack());
      advance_to_result();
    }

    void attack_resolution_wizard::with_vd_balance(unsigned int balance)
    {
      _outcome = std::make_shared<combat::outcome>(step_as<combat::final_damage>()->with_balance(balance).end_attack());
      advance_to_result();
    }

    void attack_resolution_wizard::cancel()
    {
      emit back_issued();
    }

    void attack_resolution_wizard::advance()
    {
      if (layout->currentWidget() != result_page)
        layout->setCurrentIndex(layout->currentIndex() + 1);
      else
        emit outcome(_outcome);
    }

    void attack_resolution_wizard::advance_to_result()
    {
      //result_page->set
      layout->setCurrentWidget(result_page);
    }

}}
