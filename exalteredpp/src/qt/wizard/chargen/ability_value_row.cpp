#include "wizard/chargen/ability_value_row.h"
#include "widget/std_compatible.h"
#include "layout/layout_constants.h"
#include "layout/qborderlayout.h"
#include <QDialog>
#include <QVariant>
#include <QApplication>

namespace qt { namespace wizard {

    ability_value_row::ability_value_row(const ability::ability& model_ability)
      :_ability(model_ability)
    {
      increase_ability_button = new QPushButton("+");
      decrease_ability_button = new QPushButton("-");
      make_favorite_button = new QPushButton("*");
      increase_ability_button->setFixedSize(layout::SQUARE_BUTTON_STD_SIZE);
      decrease_ability_button->setFixedSize(layout::SQUARE_BUTTON_STD_SIZE);
      make_favorite_button   ->setFixedSize(layout::SQUARE_BUTTON_STD_SIZE);

      connect(increase_ability_button, &QPushButton::clicked, this, &ability_value_row::on_increase);
      connect(decrease_ability_button, &QPushButton::clicked, this, &ability_value_row::on_decrease);
      connect(make_favorite_button,    &QPushButton::clicked, this, &ability_value_row::on_fav_toggle);

      ability_value_label = new QLabel(QString::number(_ability.value()));
      ability_value_label->setFixedSize(layout::SQUARE_BUTTON_STD_SIZE);
      ability_name_label = label(_ability.name());

      if (_ability.favored())
        ability_name_label->setStyleSheet("font-weight: bold");
      else
        ability_name_label->setStyleSheet("font-weight: normal");
    }

    void ability_value_row::on_decrease()
    {
      --_ability;
      ability_value_label->setText(QString::number(_ability.value()));
      emit ability_change();
    }

    void ability_value_row::on_increase()
    {
      ++_ability;
      ability_value_label->setText(QString::number(_ability.value()));
      emit ability_change();
    }

    void ability_value_row::on_fav_toggle()
    {
      _ability.set_favored(!_ability.favored());

      if (_ability.favored())
        ability_name_label->setStyleSheet("font-weight: bold");
      else
        ability_name_label->setStyleSheet("font-weight: normal");

      emit ability_change();
    }

    void ability_value_row::update_operations(bool allow_increase, bool allow_decrease, bool allow_favorite, bool allow_unfavorite)
    {
      increase_ability_button->setEnabled(allow_increase);
      decrease_ability_button->setEnabled(allow_decrease);
      bool allow_fav = (_ability.favored() && allow_unfavorite)
          || (!_ability.favored() && allow_favorite);
      make_favorite_button->setEnabled(allow_fav);
    }

    ability::ability ability_value_row::ability() const
    {
      return _ability;
    }

    void ability_value_row::add_row(QFormLayout *form) const
    {      
      QHBoxLayout *buttons_layout = new QHBoxLayout;
      buttons_layout->addWidget(decrease_ability_button);
      buttons_layout->addWidget(ability_value_label    );
      buttons_layout->addWidget(increase_ability_button);
      buttons_layout->addWidget(make_favorite_button   );

      form->addRow(ability_name_label, buttons_layout);
    }
} }
