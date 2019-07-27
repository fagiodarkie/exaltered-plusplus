#include "screen/qdefense_values_screen.h"

#include <QFormLayout>
#include <QGroupBox>
#include <QLabel>
#include <QScrollArea>


namespace qt {
  namespace screen {

    using namespace character::ability_names;
    using namespace character::attribute_names;

    qdefense_values_screen::qdefense_values_screen(const std::shared_ptr<character::character> c,
                                                   const calculator::derived_value_calculator& derived_values,
                                                   QWidget *parent)
      : QWidget(parent), _character(c), _calculator(derived_values)
    {
      physical_parry_ability = new QComboBox;

      QList<QString> parry_abilities = {ABILITY_NAME.at(MELEE).c_str(),
                                        ABILITY_NAME.at(MARTIAL_ARTS).c_str(),
                                        ABILITY_NAME.at(ATHLETICS).c_str()};
      physical_parry_ability->addItems(parry_abilities);
      connect(physical_parry_ability, &QComboBox::currentTextChanged, this, &qdefense_values_screen::update_values);
      update_values();
    }

    void qdefense_values_screen::update_values()
    {
      QWidget *form_widget = new QWidget, *parry_ability_selector_widget = new QWidget;
      QGroupBox *phys_form_widget = new QGroupBox("Physical DVs"), *mental_form_widget = new QGroupBox("Mental DVs");
      QFormLayout* phys_form = new QFormLayout, *mental_form = new QFormLayout;
      QHBoxLayout* parry_ability_selector = new QHBoxLayout;

      parry_ability_selector->addWidget(new QLabel("Physical Parry Ability"));
      parry_ability_selector->addWidget(physical_parry_ability);
      ability_enum ability = commons::reverse_search_in_map(ABILITIES, ABILITY_NAME, physical_parry_ability->currentText().toStdString());
      parry_ability_selector_widget->setLayout(parry_ability_selector);

      phys_form->addRow("Dodge DV", new QLabel(QString::number(_calculator.compute_dodge_dv(*_character))));
      phys_form->addRow("Parry DV", new QLabel(QString::number(_calculator.compute_parry_dv(*_character, ability))));
      phys_form->addRow("Heavy Parry DV", new QLabel(QString::number(_calculator.compute_heavy_parry_dv(*_character, ability))));
      phys_form_widget->setLayout(phys_form);

      mental_form->addRow("Mental Dodge DV", new QLabel(QString::number(_calculator.compute_mental_dodge_dv(*_character))));
      mental_form->addRow("Charisma Parry DV", new QLabel(QString::number(_calculator.compute_mental_parry_dv(*_character, CHARISMA))));
      mental_form->addRow("Manipulation Parry DV", new QLabel(QString::number(_calculator.compute_mental_parry_dv(*_character, MANIPULATION))));
      mental_form->addRow("Appearance Parry DV", new QLabel(QString::number(_calculator.compute_mental_parry_dv(*_character, APPEARANCE))));
      mental_form_widget->setLayout(mental_form);

      QVBoxLayout *v_layout = new QVBoxLayout, *inner_layout = new QVBoxLayout;
      inner_layout->addWidget(parry_ability_selector_widget);
      inner_layout->addWidget(phys_form_widget);
      inner_layout->addWidget(mental_form_widget);
      form_widget->setLayout(inner_layout);

      QScrollArea *scroll_area = new QScrollArea;
      scroll_area->setWidgetResizable(true);
      scroll_area->setWidget(form_widget);

      v_layout->addWidget(scroll_area);

      setLayout(v_layout);
    }
  }
}
