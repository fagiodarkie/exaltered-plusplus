#include "wizard/ability_value_row.h"
#include "widget/std_compatible.h"
#include "layout/layout_constants.h"
#include "layout/qborderlayout.h"
#include <QDialog>
#include <QVariant>

namespace qt { namespace wizard {

    const char* ability_value_row::REFERRED_ABILITY = "referred_ability";
    const char* ability_value_row::REFERRED_SUB_ABILITY = "referred_sub_ability";

    ability_value_row::ability_value_row(const ability_group& model_ability_group)
      :_ability(model_ability_group)
    {
      add_declination = new QPushButton("Add Declination");
      connect(add_declination, &QPushButton::clicked, this, &ability_value_row::show_declination_wizard);

      declination_dialog = new widget::add_ability_declination_dialog;
      connect(declination_dialog, &widget::add_ability_declination_dialog::declination_selected, this, &ability_value_row::add_new_declination);

      QList<QString> current_declinations;
      for (auto ability: _ability.get_ability_names())
        {
          current_declinations.append(ability.declination.c_str());
          QPushButton *increase = new QPushButton("+"), *decrease = new QPushButton("-"), *fav = new QPushButton("*");
          increase->setFixedSize(layout::SQUARE_BUTTON_STD_SIZE);
          decrease->setFixedSize(layout::SQUARE_BUTTON_STD_SIZE);
          fav     ->setFixedSize(layout::SQUARE_BUTTON_STD_SIZE);

          connect(increase, &QPushButton::clicked, this, &ability_value_row::on_increase);
          connect(decrease, &QPushButton::clicked, this, &ability_value_row::on_decrease);
          connect(fav,      &QPushButton::clicked, this, &ability_value_row::on_fav_toggle);

          increase->setProperty(REFERRED_SUB_ABILITY, QVariant(ability.declination.c_str()));
          decrease->setProperty(REFERRED_SUB_ABILITY, QVariant(ability.declination.c_str()));
          fav     ->setProperty(REFERRED_SUB_ABILITY, QVariant(ability.declination.c_str()));

          increase_ability_buttons[ability.declination] = increase;
          decrease_ability_buttons[ability.declination] = decrease;
          make_favorite_buttons[ability.declination] = fav;

          widget::ability_declination_selector *declination = new widget::ability_declination_selector(ability, false, false);
          change_declination_buttons[ability.declination] = declination;

          QLabel *value = label(_ability.get_ability(ability.declination).get_value());
          value->setFixedSize(layout::SQUARE_BUTTON_STD_SIZE);
          ability_value_labels[ability.declination] = value;
        }

      declination_dialog->set_prohibited_declinations(current_declinations);
    }

    void ability_value_row::add_new_declination(const QString& new_declination_name)
    {
      _ability.add_ability(character::ability(new_declination_name.toStdString()));
      emit ability_change();
    }

    void ability_value_row::show_declination_wizard() const
    {
      declination_dialog->show();
    }

    void ability_value_row::on_decrease()
    {
      auto sub_ability = sender()->property(REFERRED_SUB_ABILITY).toString().toStdString();

      _ability.set_ability_value(sub_ability, _ability.get_ability(sub_ability).get_ability_value() - 1);
      ability_value_labels[sub_ability]->setText(_ability.get_ability(sub_ability).get_value().c_str());

      emit ability_change();
    }

    void ability_value_row::on_increase()
    {
      auto sub_ability = sender()->property(REFERRED_SUB_ABILITY).toString().toStdString();
      _ability.set_ability_value(sub_ability, _ability.get_ability(sub_ability).get_ability_value() + 1);
      ability_value_labels[sub_ability]->setText(_ability.get_ability(sub_ability).get_value().c_str());

      emit ability_change();
    }

    void ability_value_row::on_fav_toggle()
    {
      auto sub_ability = sender()->property(REFERRED_SUB_ABILITY).toString().toStdString();
      bool currently_favored = _ability.get_ability(sub_ability).is_favourite();
      _ability.set_favourite(!currently_favored, sub_ability);

      change_declination_buttons[sub_ability]->set_favored(!currently_favored);

      emit ability_change();
    }

    void ability_value_row::update_operations(const std::string& declination, bool allow_increase, bool allow_decrease, bool allow_favorite, bool allow_unfavorite)
    {
      increase_ability_buttons[declination]->setEnabled(allow_increase);
      decrease_ability_buttons[declination]->setEnabled(allow_decrease);
      bool allow_fav = (_ability.get_ability(declination).is_favourite() && allow_unfavorite)
          || (!_ability.get_ability(declination).is_favourite() && allow_favorite);
      make_favorite_buttons[declination]->setEnabled(allow_fav);
    }

    ability_group ability_value_row::ability() const
    {
      return _ability;
    }

    void ability_value_row::add_rows(QFormLayout *form) const
    {      
      for (auto ability: _ability.get_ability_names())
        {
          QHBoxLayout *buttons_layout = new QHBoxLayout;
          buttons_layout->addWidget(decrease_ability_buttons  [ability.declination]);
          buttons_layout->addWidget(ability_value_labels      [ability.declination]);
          buttons_layout->addWidget(increase_ability_buttons  [ability.declination]);
          buttons_layout->addWidget(make_favorite_buttons     [ability.declination]);

          form->addRow(change_declination_buttons[ability.declination], buttons_layout);
        }

      if (character::ability_names::has_declination(_ability.get_ability_enum()))
        {
          form->addRow(add_declination, new QWidget);
        }
    }
} }
