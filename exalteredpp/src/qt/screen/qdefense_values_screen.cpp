#include "screen/qdefense_values_screen.h"

#include <QFormLayout>
#include <QGroupBox>
#include <QScrollArea>
#include "layout/qborderlayout.h"
#include "label/interfacelabels.h"

namespace qt {
  namespace screen {

    using namespace ability;
    using namespace labels::dv_labels;

    qdefense_values_screen::qdefense_values_screen(const std::shared_ptr<character::character> c,
                                                   const calculator::derived_value_calculator& derived_values,
                                                   QWidget *parent)
      : QWidget(parent), _character(c), _calculator(derived_values),
        dodge_dv        (new QLabel),
        parry_dv        (new QLabel),
        heavy_parry_dv  (new QLabel),
        parry_balance   (new QLabel),
        dodge_balance   (new QLabel),
        mental_dodge_dv (new QLabel),
        charisma_pdv    (new QLabel),
        manipulation_pdv(new QLabel),
        appearance_pdv  (new QLabel),
        resilience      (new QLabel),
        natural_soak    (new QLabel)
    {
      physical_parry_ability = new QComboBox;

      QList<QString> parry_abilities = {ABILITY_NAME.at(ability_enum::MELEE).c_str(),
                                        ABILITY_NAME.at(ability_enum::MARTIAL_ARTS).c_str(),
                                        ABILITY_NAME.at(ability_enum::ATHLETICS).c_str()};
      physical_parry_ability->addItems(parry_abilities);
      connect(physical_parry_ability, &QComboBox::currentTextChanged, this, &qdefense_values_screen::update_values);
      QWidget *form_widget = new QWidget, *parry_ability_selector_widget = new QWidget, *central_dv_widget = new QWidget;
      QGroupBox *phys_form_widget = new QGroupBox(PHYS_VDS), *mental_form_widget = new QGroupBox(MENTAL_VDS);
      QFormLayout* phys_form = new QFormLayout, *mental_form = new QFormLayout;
      QHBoxLayout* parry_ability_selector = new QHBoxLayout;

      attack_wizard = new QPushButton("Start Attack");
      connect(attack_wizard, &QPushButton::clicked, this, &qdefense_values_screen::attack_wizard_invoked);
      defense_wizard = new QPushButton("Defend from Attack");
      connect(defense_wizard, &QPushButton::clicked, this, &qdefense_values_screen::defense_wizard_invoked);

      parry_ability_selector->addWidget(new QLabel(PHYS_PARRY_ABILITY));
      parry_ability_selector->addWidget(physical_parry_ability);
      parry_ability_selector_widget->setLayout(parry_ability_selector);
      update_values();

      phys_form->addRow(DODGE_DV, dodge_dv      );
      phys_form->addRow(DODGE_BAL, dodge_balance);
      phys_form->addRow(PARRY_DV, parry_dv      );
      phys_form->addRow(H_PARRY_DV, heavy_parry_dv);
      phys_form->addRow(PARRY_BAL, parry_balance);
      phys_form->addRow(NAT_SOAK, natural_soak);
      phys_form_widget->setLayout(phys_form);

      mental_form->addRow(M_DODGE_DV        , mental_dodge_dv);
      mental_form->addRow(M_CHARISMA_PDV    , charisma_pdv);
      mental_form->addRow(M_MANIPULATION_PDV, manipulation_pdv);
      mental_form->addRow(M_APPEARANCE_PDV  , appearance_pdv);
      mental_form->addRow(M_RESILIENCE      , resilience);
      mental_form_widget->setLayout(mental_form);

      QVBoxLayout *v_layout = new QVBoxLayout, *dv_layout = new QVBoxLayout;
      dv_layout->addWidget(phys_form_widget);
      dv_layout->addWidget(mental_form_widget);
      central_dv_widget->setLayout(dv_layout);

      QVBoxLayout *buttons_layout = new QVBoxLayout;
      buttons_layout->addWidget(attack_wizard);
      buttons_layout->addWidget(defense_wizard);
      QWidget* buttons = new QWidget;
      buttons->setLayout(buttons_layout);

      layout::QBorderLayout *inner_layout = new layout::QBorderLayout;
      inner_layout->addWidget(parry_ability_selector_widget, layout::QBorderLayout::North);
      inner_layout->addWidget(central_dv_widget, layout::QBorderLayout::Center);
      inner_layout->addWidget(buttons, layout::QBorderLayout::South);
      form_widget->setLayout(inner_layout);

      QScrollArea *scroll_area = new QScrollArea;
      scroll_area->setWidgetResizable(true);
      scroll_area->setWidget(form_widget);

      v_layout->addWidget(scroll_area);
      setLayout(v_layout);
    }

    void qdefense_values_screen::update_values()
    {
      ability_enum ability = commons::reverse_search_in_map(ABILITIES, ABILITY_NAME, physical_parry_ability->currentText().toStdString());

      auto character_vds = _calculator.compute_physical_vd(*_character, ability);
      auto character_mvds = _calculator.compute_mental_vd(*_character);
      auto soaks = _calculator.compute_soak_values(*_character);

      dodge_dv        ->setText(QString::number(character_vds.dodge_vd));
      dodge_balance   ->setText(QString::number(character_vds.dodge_balance));
      parry_dv        ->setText(QString::number(character_vds.parry_vd));
      heavy_parry_dv  ->setText(QString::number(character_vds.tower_parry_vd));
      parry_balance   ->setText(QString::number(character_vds.parry_balance));

      mental_dodge_dv ->setText(QString::number(character_mvds.mental_dodge_vd));
      charisma_pdv    ->setText(QString::number(character_mvds.charisma_parry_vd));
      manipulation_pdv->setText(QString::number(character_mvds.manipulation_parry_vd));
      appearance_pdv  ->setText(QString::number(character_mvds.appearance_parry_vd));
      resilience      ->setText(QString::number(character_mvds.resilience));

      natural_soak    ->setText(QString("%1U / %2L / %3A")
                        .arg(soaks.natural_soak[combat::damage_type_enum::BASHING])
                        .arg(soaks.natural_soak[combat::damage_type_enum::LETHAL])
                        .arg(soaks.natural_soak[combat::damage_type_enum::AGGRAVATED]));
    }
  }
}
