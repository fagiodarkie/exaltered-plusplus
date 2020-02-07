#include "wizard/phys_attack/attack_result_page.h"

#include "layout/qborderlayout.h"

#include "label/interfacelabels.h"

namespace qt {
  namespace wizard {

    using namespace labels::wizards::physical_attack;

    attack_result_page::attack_result_page(QWidget *parent) : QWidget(parent)
    {
      result = new QLabel;
      layout::QBorderLayout *outer = new layout::QBorderLayout;

      outer->addWidget(_progress_bar, layout::QBorderLayout::North);
      outer->addWidget(result, layout::QBorderLayout::Center);
      outer->addWidget(buttons_layout(), layout::QBorderLayout::South);

      setLayout(outer);

      enable_next();
    }

    void attack_result_page::with_outcome(std::shared_ptr<combat::outcome> attack_outcome)
    {
      QString result_copy;

      if (!attack_outcome->was_hit())
        {
          result_copy = ATTACK_RESULT_MISSED;
        }
      else
        {
          QString target_hit = combat::BODY_TARGET_NAME.at(attack_outcome->target_hit()).c_str();
          if (attack_outcome->final_damage() > 0)
            result_copy = ATTACK_RESULT_WITH_DAMAGE.arg(target_hit).arg(attack_outcome->final_damage());
          else
            result_copy = ATTACK_RESULT_NO_DAMAGE.arg(target_hit);

          if (attack_outcome->was_knocked_down())
            result_copy += KNOCKDOWN;
          else if (attack_outcome->was_pushed())
            result_copy += KNOCKBACK.arg(attack_outcome->meters_pushed());
        }

      if (attack_outcome->counter_available())
        result_copy += ATTACK_RESULT_COUNTER;

      result->setText(result_copy);
    }
}
}
