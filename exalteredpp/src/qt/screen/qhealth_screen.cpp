#include "screen/qhealth_screen.h"

#include "label/interfacelabels.h"
#include "layout/qborderlayout.h"
#include "layout/layout_helper_factories.h"

#include <QFormLayout>
#include <QGroupBox>

namespace qt { namespace screen {

    using namespace labels::health_labels;

    qhealth_screen::qhealth_screen(std::shared_ptr<character::character> character,
                                                 std::shared_ptr<manager::character_manager> manager,
                                                 QWidget *parent)
      : QWidget(parent),
      _character(character),
      _manager(manager)
    {
      _deal_heal_button = new QPushButton(HEAL_CHARACTER.arg(character->name().c_str()));
      connect(_deal_heal_button, &QPushButton::clicked, this, &qhealth_screen::on_deal_heal_issued);

      _deal_radio = new QRadioButton(DEAL_DAMAGE, this);
      _heal_radio = new QRadioButton(HEAL_DAMAGE, this);
      _heal_radio->setChecked(true);
      connect(_deal_radio, &QRadioButton::clicked, this, &qhealth_screen::on_deal_heal_switched);
      connect(_heal_radio, &QRadioButton::clicked, this, &qhealth_screen::on_deal_heal_switched);

      _value_label = new QLabel(HEAL_DAMAGE_VALUE);
      _health_label = new QLabel(labels::PARTIAL_OVER_TOTAL(character->health().current_health(), character->health().total_health()));
      _amount_box = new QSpinBox;

      layout::QBorderLayout *outer = new layout::QBorderLayout;

      QVBoxLayout *heal_deal_layout = new QVBoxLayout;
      heal_deal_layout->setAlignment(Qt::AlignTop);

      QFormLayout *info = new QFormLayout;
      info->addRow(CURRENT_HEALTH, _health_label);
      info->addRow(HURT_THRESHOLD, new QLabel(QString::number(character->health().injured_health_level())));
      info->addRow(DYING_THRESHOLD, new QLabel(QString::number(character->health().dying_health_level())));
      QGroupBox *infoBox = new QGroupBox(HEALTH_TITLE);
      infoBox->setLayout(info);

      QWidget* spin = layout::horizontal_couple(_value_label, _amount_box);

      heal_deal_layout->addWidget(infoBox);
      heal_deal_layout->addWidget(_deal_radio);
      heal_deal_layout->addWidget(_heal_radio);
      heal_deal_layout->addWidget(spin);
      heal_deal_layout->addWidget(_deal_heal_button);
      QWidget *heal_deal_w = new QWidget;
      heal_deal_w->setLayout(heal_deal_layout);

      QLabel* summary_label = new QLabel(PENALTY_SUMMARY);
      summary_label->setWordWrap(true);

      outer->addWidget(heal_deal_w, layout::QBorderLayout::Center);
      outer->addWidget(summary_label, layout::QBorderLayout::North);
      setLayout(outer);
    }


    void qhealth_screen::on_deal_heal_switched()
    {
      if (_deal_radio->isChecked())
        {
          _deal_heal_button->setText(DAMAGE_CHARACTER.arg(_character->name().c_str()));
          _value_label->setText(DEAL_DAMAGE_VALUE);
        }
      else
        {
          _deal_heal_button->setText(HEAL_CHARACTER.arg(_character->name().c_str()));
          _value_label->setText(HEAL_DAMAGE_VALUE);
        }
    }

    void qhealth_screen::on_deal_heal_issued()
    {
      if (_deal_radio->isChecked())
        _character->health().deal_damage(_amount_box->value());
      else
        _character->health().heal_damage(_amount_box->value());

      _amount_box->setValue(0);

      _manager->save_character(_character);
      _health_label->setText(labels::PARTIAL_OVER_TOTAL(_character->health().current_health(), _character->health().total_health()));
    }
}}
