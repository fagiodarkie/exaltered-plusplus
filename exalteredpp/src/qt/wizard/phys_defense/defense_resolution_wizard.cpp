#include "wizard/phys_defense/defense_resolution_wizard.h"

namespace qt { namespace wizard {


    defense_resolution_wizard::defense_resolution_wizard(std::shared_ptr<character::character> character,
                                                          const calculator::derived_value_calculator& worker,
                                                          QWidget* parent)

      : QWidget(parent), _defender(character), _worker(worker)
    {
      _step = std::make_shared<combat::pre_precision_defense_declaration>(combat::attack_declaration::declare().defend());

      defense_declaration = new defense_declaration_page(_defender, _worker);
      defense_declaration->on_back_issued([this]() { emit back_issued(); });
      connect(defense_declaration, &defense_declaration_page::defense_selected, this, &defense_resolution_wizard::chosen_vd);

      attack_parameters = new attack_parameters_page;
      attack_parameters->disable_back();
      // connect

      final_damage_input = new final_damage_input_page;
      final_damage_input->disable_back();
      // connect

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

    }

    void defense_resolution_wizard::with_final_damage(unsigned int final_damage)
    {

    }

    void defense_resolution_wizard::roll_final_damage()
    {

    }

    void defense_resolution_wizard::chosen_vd(combat::target_vd vd, int vd_modifier, bool will_counter)
    {

    }

    void defense_resolution_wizard::knockback(unsigned int devoted_successes)
    {

    }

    void defense_resolution_wizard::knockdown(unsigned int devoted_successes)
    {

    }

    void defense_resolution_wizard::no_knocking()
    {

    }

    void defense_resolution_wizard::advance()
    {

    }

    void defense_resolution_wizard::advance_to_result()
    {

    }

  }
}
