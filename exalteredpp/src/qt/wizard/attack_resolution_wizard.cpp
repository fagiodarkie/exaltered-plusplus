#include "wizard/attack_resolution_wizard.h"

namespace qt { namespace wizard {
    attack_resolution_wizard::attack_resolution_wizard(std::shared_ptr<character::character> character,
                                                       const calculator::derived_value_calculator& worker,
                                                       QWidget* parent)
      : QWidget(parent), _attacker(character), _worker(worker)
    {
      _step = std::make_shared<combat::attack_declaration>(combat::attack_declaration::declare());

      attack_declaration = new attack_declaration_precision_page(_attacker);
      attack_declaration->on_back_issued([this]() { cancel(); });
      connect(attack_declaration, &attack_declaration_precision_page::attack_selected, this, &attack_resolution_wizard::attack_with);

      layout = new QStackedLayout;
      QList<QWidget*> pages = { attack_declaration };

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
                     unsigned int external_bonus, unsigned int external_malus)
    {

    }

    void attack_resolution_wizard::cancel()
    {

    }

    void attack_resolution_wizard::advance()
    {

    }



}}
