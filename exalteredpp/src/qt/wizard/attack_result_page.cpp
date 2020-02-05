#include "wizard/attack_result_page.h"

#include "layout/qborderlayout.h"

namespace qt {
  namespace wizard {
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
          result_copy = "The attack precision was lesser than the chosen VD: the attack was nullified.";
        }
      else
        {
          QString target_hit = combat::BODY_TARGET_NAME.at(attack_outcome->target_hit()).c_str();
          if (attack_outcome->final_damage() > 0)
            result_copy = QString("The attack connected with the defender's %0, dealing %1 damage points.")
                .arg(target_hit)
                .arg(attack_outcome->final_damage());
          else
            result_copy = QString("The attack connected with the defender's %0, but dealt no damage.")
                .arg(target_hit);

          if (attack_outcome->was_knocked_down())
            result_copy += "\r\nThe defender was knocked down by the force of the blow!";
          else if (attack_outcome->was_pushed())
            result_copy += QString("\r\nThe defender was pushed away %0 meters by the force of the blow!")
                .arg(attack_outcome->meters_pushed());
        }

      if (attack_outcome->counter_available())
        result_copy += "\r\nThe defender may counter the attack, if he so wishes.";

      result->setText(result_copy);
    }
}
}
