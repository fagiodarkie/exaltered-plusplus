#include "wizard/ability_value_row.h"
#include <QVariant>

namespace qt { namespace wizard {

    const char* ability_value_row::REFERRED_ABILITY = "referred_ability";
    const char* ability_value_row::REFERRED_SUB_ABILITY = "referred_sub_ability";

    ability_value_row::ability_value_row(const ability_group& model_ability_group)
      :_ability(model_ability_group)
    {
      add_declination = new QPushButton("Add Declination");

      for (auto ability: _ability.get_abilities())
        {
          QPushButton *increase = new QPushButton("+"), *decrease = new QPushButton("-"), *change = new QPushButton(ability.get_name().c_str());
          increase->setProperty(REFERRED_ABILITY, QVariant(_ability.get_ability_enum()));
          increase->setProperty(REFERRED_SUB_ABILITY, QVariant(ability.get_name().c_str()));
          decrease->setProperty(REFERRED_ABILITY, QVariant(_ability.get_ability_enum()));
          decrease->setProperty(REFERRED_SUB_ABILITY, QVariant(ability.get_name().c_str()));
          change->setProperty(REFERRED_ABILITY, QVariant(_ability.get_ability_enum()));
          change->setProperty(REFERRED_SUB_ABILITY, QVariant(ability.get_name().c_str()));
          increase_ability_buttons[ability.get_name()] = increase;
          decrease_ability_buttons[ability.get_name()] = decrease;
          change_declination_buttons[ability.get_name()] = change;

          if (!_ability.has_abilities())
            change->setEnabled(false);

          QLabel *value = new QLabel(QString::number(ability.get_ability_value()));
          ability_value_labels[ability.get_name()] = value;


        }

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
      for (auto ability: _ability.get_abilities())
        {
          QHBoxLayout *buttons_layout = new QHBoxLayout;
          buttons_layout->addWidget(decrease_ability_buttons[ability.get_name()]);
          buttons_layout->addWidget(ability_value_labels[ability.get_name()]);
          buttons_layout->addWidget(increase_ability_buttons[ability.get_name()]);
          form->addRow(change_declination_buttons[ability.get_name()], buttons_layout);
        }

      if (character::ability_names::has_declination(_ability.get_ability_enum()))
        {
          form->addRow(add_declination);
        }
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
