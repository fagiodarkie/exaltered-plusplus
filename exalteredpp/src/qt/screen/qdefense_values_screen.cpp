#include "screen/qdefense_values_screen.h"

#include <QFormLayout>
#include <QGroupBox>
#include <QScrollArea>
#include "layout/qborderlayout.h"
#include "label/interfacelabels.h"

namespace qt {
  namespace screen {

    using namespace character::ability_names;
    using namespace character::attribute_names;
    using namespace labels::dv_labels;

    qdefense_values_screen::qdefense_values_screen(const std::shared_ptr<character::character> c,
                                                   const calculator::derived_value_calculator& derived_values,
                                                   QWidget *parent)
      : QWidget(parent), _character(c), _calculator(derived_values),
        dodge_dv        (nullptr),
        parry_dv        (nullptr),
        heavy_parry_dv  (nullptr),
        mental_dodge_dv (nullptr),
        charisma_pdv    (nullptr),
        manipulation_pdv(nullptr),
        appearance_pdv  (nullptr)
    {
      physical_parry_ability = new QComboBox;

      QList<QString> parry_abilities = {ABILITY_NAME.at(MELEE).c_str(),
                                        ABILITY_NAME.at(MARTIAL_ARTS).c_str(),
                                        ABILITY_NAME.at(ATHLETICS).c_str()};
      physical_parry_ability->addItems(parry_abilities);
      connect(physical_parry_ability, &QComboBox::currentTextChanged, this, &qdefense_values_screen::update_values);
      QWidget *form_widget = new QWidget, *parry_ability_selector_widget = new QWidget, *central_dv_widget = new QWidget;
      QGroupBox *phys_form_widget = new QGroupBox(PHYS_VDS), *mental_form_widget = new QGroupBox(MENTAL_VDS);
      QFormLayout* phys_form = new QFormLayout, *mental_form = new QFormLayout;
      QHBoxLayout* parry_ability_selector = new QHBoxLayout;

      parry_ability_selector->addWidget(new QLabel(PHYS_PARRY_ABILITY));
      parry_ability_selector->addWidget(physical_parry_ability);
      parry_ability_selector_widget->setLayout(parry_ability_selector);
      update_values();

      phys_form->addRow(DODGE_DV, dodge_dv      );
      phys_form->addRow(PARRY_DV, parry_dv      );
      phys_form->addRow(H_PARRY_DV, heavy_parry_dv);
      phys_form_widget->setLayout(phys_form);

      mental_form->addRow(M_DODGE_DV        , mental_dodge_dv);
      mental_form->addRow(M_CHARISMA_PDV    , charisma_pdv);
      mental_form->addRow(M_MANIPULATION_PDV, manipulation_pdv);
      mental_form->addRow(M_APPEARANCE_PDV  , appearance_pdv);
      mental_form_widget->setLayout(mental_form);

      QVBoxLayout *v_layout = new QVBoxLayout, *dv_layout = new QVBoxLayout;
      dv_layout->addWidget(phys_form_widget);
      dv_layout->addWidget(mental_form_widget);
      central_dv_widget->setLayout(dv_layout);

      layout::QBorderLayout *inner_layout = new layout::QBorderLayout;
      inner_layout->addWidget(parry_ability_selector_widget, layout::QBorderLayout::North);
      inner_layout->addWidget(central_dv_widget, layout::QBorderLayout::Center);
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

      if (dodge_dv == nullptr)
        {
          dodge_dv            = new QLabel;
          parry_dv            = new QLabel;
          heavy_parry_dv      = new QLabel;
          mental_dodge_dv     = new QLabel;
          charisma_pdv        = new QLabel;
          manipulation_pdv    = new QLabel;
          appearance_pdv      = new QLabel;
        }

      dodge_dv        ->setText(QString::number(_calculator.compute_dodge_dv(*_character)));
      parry_dv        ->setText(QString::number(_calculator.compute_parry_dv(*_character, ability)));
      heavy_parry_dv  ->setText(QString::number(_calculator.compute_heavy_parry_dv(*_character, ability)));
      mental_dodge_dv ->setText(QString::number(_calculator.compute_mental_dodge_dv(*_character)));
      charisma_pdv    ->setText(QString::number(_calculator.compute_mental_parry_dv(*_character, CHARISMA)));
      manipulation_pdv->setText(QString::number(_calculator.compute_mental_parry_dv(*_character, MANIPULATION)));
      appearance_pdv  ->setText(QString::number(_calculator.compute_mental_parry_dv(*_character, APPEARANCE)));
    }
  }
}
