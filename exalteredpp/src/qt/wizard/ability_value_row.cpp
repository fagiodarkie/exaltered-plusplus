#include "wizard/ability_value_row.h"

namespace qt { namespace wizard {

    const char* ability_value_row::REFERRED_ABILITY = "referred_ability";
    const char* ability_value_row::REFERRED_SUB_ABILITY = "referred_sub_ability";

    ability_value_row::ability_value_row(const ability_group& model_ability_group)
      :_ability(model_ability_group)
    {
      update_labels();
    }

    void ability_value_row::update(const ability_group& ability)
    {
      _ability = ability;
      update_labels();
    }

    ability_group ability_value_row::ability() const
    {
      return _ability;
    }

    void ability_value_row::add_rows(QFormLayout *form) const
    {
      // TODO
    }

    void ability_value_row::update_labels()
    {
      //label->setText(creation_wizard::ATTRIBUTE_WITH_POINTS(ability_name, value));
      //label->setStyleSheet(is_favored ? "font-weight: bold" : "");


      //label = new QLabel(ability_name + " (999)");
      //label->setTextFormat(Qt::RichText);
      //label->setStyleSheet("font-weight: bold");
      //increase = new QPushButton("+");
      //increase->setFixedSize(layout::SQUARE_BUTTON_STD_SIZE);
      //increase->setProperty(REFERRED_ABILITY, ability);
      //
      //decrease = new QPushButton("-");
      //decrease->setFixedSize(layout::SQUARE_BUTTON_STD_SIZE);
      //decrease->setProperty(REFERRED_ABILITY, ability);
    }

} }
