#include "wizard/phys_defense/defense_resolution_wizard.h"

#include "dependencies.h"

namespace qt { namespace wizard {


    defense_resolution_wizard::defense_resolution_wizard(std::shared_ptr<character::character> character,
                                                          const calculator::derived_value_calculator& worker,
                                                          QWidget* parent)

      : QWidget(parent), _defender(character), _worker(worker)
    {
      _step = std::make_shared<combat::pre_precision_defense_declaration>(combat::attack_declaration::declare().defend());

      defense_declaration = new defense_declaration_page(_defender, _worker);
      defense_declaration->on_back_issued([this]() { emit back_issued(); });
      connect(defense_declaration, &defense_declaration_page::parry, this, &defense_resolution_wizard::parry);
      connect(defense_declaration, &defense_declaration_page::dodge, this, &defense_resolution_wizard::dodge);

      attack_parameters = new attack_parameters_page;
      attack_parameters->disable_back();
      connect(attack_parameters, &attack_parameters_page::attack_parameters, this, &defense_resolution_wizard::with_precision);

      final_damage_input = new final_damage_input_page;
      final_damage_input->disable_back();
      connect(final_damage_input, &final_damage_input_page::roll_damage, this, &defense_resolution_wizard::roll_final_damage);
      connect(final_damage_input, &final_damage_input_page::with_damage, this, &defense_resolution_wizard::with_final_damage);

      final_damage = new final_damage_results_push_knock_page;
      final_damage->disable_back();
      connect(final_damage, &final_damage_results_push_knock_page::knockback,   this, &defense_resolution_wizard::knockback);
      connect(final_damage, &final_damage_results_push_knock_page::knockdown,   this, &defense_resolution_wizard::knockdown);
      connect(final_damage, &final_damage_results_push_knock_page::no_knocking, this, &defense_resolution_wizard::no_knocking);

      result_page = new attack_result_page;
      result_page->disable_back();
      result_page->on_next_issued([this]() { advance(); });

      layout = new QStackedLayout;
      QList<QWidget*> pages = { defense_declaration, attack_parameters, final_damage_input, final_damage, result_page };

      for (unsigned int i = 0; i < pages.size(); ++i)
        {
          layout->addWidget(pages.at(i));
          dynamic_cast<widget::with_progress_bar*>(pages.at(i))->set_progress_bar_status(i, pages.size());
        }
      layout->setCurrentIndex(0);

      setLayout(layout);
    }


    void defense_resolution_wizard::with_precision(combat::body_target target, combat::damage_type_enum damage_type, unsigned int successes, unsigned int base_damage, unsigned int min_damage, unsigned int drill)
    {
      _damage_type = damage_type;

      if (target != combat::body_target::NO_TARGET)
        _step = std::make_shared<combat::precision_roll>(step_as<combat::precision_roll>()->target(target));

      _step = std::make_shared<combat::vd_application>(step_as<combat::precision_roll>()->with_successes(successes));

      if (!step_as<combat::vd_application>()->hits())
        {
          _outcome = std::make_shared<combat::outcome>(step_as<combat::vd_application>()->on_fail());
          advance_to_result();
          return;
        }
      else _step = std::make_shared<combat::raw_damage_and_position_computation>(step_as<combat::vd_application>()->on_success()
                                                                                 .base_damage(base_damage).damage_type(damage_type)
                                                                                 .min_damage(min_damage).drill(drill));

      if (!step_as<combat::raw_damage_and_position_computation>()->passes(_worker))
        {
          _outcome = std::make_shared<combat::outcome>(step_as<combat::raw_damage_and_position_computation>()->on_fail());
          advance_to_result();
          return;
        }
      else _step = std::make_shared<combat::post_soak_damage>(step_as<combat::raw_damage_and_position_computation>()->on_pass(_worker));


      if (!step_as<combat::post_soak_damage>()->passes(_worker))
        {
          _outcome = std::make_shared<combat::outcome>(step_as<combat::post_soak_damage>()->on_fail());
          advance_to_result();
          return;
        }
      else _step = std::make_shared<combat::post_hardness_damage>(step_as<combat::post_soak_damage>()->on_pass());

      unsigned int final_damage_pool = step_as<combat::post_hardness_damage>()->attack_status()->post_soak_damage;
      final_damage_input->set_final_damage_pool(final_damage_pool);

      advance();
    }

    void defense_resolution_wizard::with_final_damage(unsigned int final_damage_value)
    {
      _step = std::make_shared<combat::final_damage>(step_as<combat::post_hardness_damage>()->with_roll(final_damage_value));

      final_damage->set_final_damage_stats(final_damage_value, _step->attack_status()->post_soak_damage);

      advance();
    }

    void defense_resolution_wizard::roll_final_damage()
    {
      _step = std::make_shared<combat::final_damage>(step_as<combat::post_hardness_damage>()->roll(dependency::dice_rollers::damage_roller(_damage_type)));

      final_damage->set_final_damage_stats(step_as<combat::final_damage>()->damage(), _step->attack_status()->post_soak_damage);

      advance();
    }

    void defense_resolution_wizard::dodge(int vd_modifier)
    {
      _chose_to_counter = false;
      _step = std::make_shared<combat::precision_roll>(step_as<combat::pre_precision_defense_declaration>()->dodge(_defender, _worker, vd_modifier));

      advance();
    }

    void defense_resolution_wizard::parry(int vd_modifier, const ability::ability_name& parry_ability, int weapon_defense, bool will_counter)
    {
      _chose_to_counter = will_counter;
      _step = std::make_shared<combat::precision_roll>(step_as<combat::pre_precision_defense_declaration>()->parry_with(_defender, _worker, parry_ability, weapon_defense, vd_modifier));

      advance();
    }

    void defense_resolution_wizard::knockdown(unsigned int devoted_successes)
    {
      _outcome = std::make_shared<combat::outcome>(step_as<combat::final_damage>()->knockdown(devoted_successes).end_attack());
      advance_to_result();
    }

    void defense_resolution_wizard::knockback(unsigned int devoted_successes)
    {
      _outcome = std::make_shared<combat::outcome>(step_as<combat::final_damage>()->knockback_meters(devoted_successes).end_attack());
      advance_to_result();
    }

    void defense_resolution_wizard::no_knocking()
    {
      _outcome = std::make_shared<combat::outcome>(step_as<combat::final_damage>()->end_attack());
      advance_to_result();
    }

    void defense_resolution_wizard::advance()
    {
      if (layout->currentWidget() == result_page)
        emit outcome(_outcome);
      else
        layout->setCurrentIndex(layout->currentIndex() + 1);
    }

    void defense_resolution_wizard::advance_to_result()
    {
      result_page->with_outcome(_outcome);
      layout -> setCurrentWidget(result_page);
    }

  }
}
