#include "widget/ability_declination_selector.h"

#include "label/interfacelabels.h"
#include "widget/std_compatible.h"

namespace qt { namespace widget {
  ability_declination_selector::ability_declination_selector(QWidget *parent)
    : QWidget(parent), _ability(character::ability_names::WAR), _is_declination_editable(true), _is_ability_editable(true), outer_widget(new QWidget)
  {
    generate_widget();
  }

  ability_declination_selector::ability_declination_selector(character::ability_names::detailed_ability ability, bool is_ability_editable, bool is_declination_editable, QWidget *parent)
    : QWidget(parent), _ability(ability), _is_declination_editable(is_declination_editable), _is_ability_editable(is_ability_editable), outer_widget(new QWidget)
  {
    generate_widget();
  }

  character::ability_names::detailed_ability ability_declination_selector::value() const
  {
    return _ability;
  }

  QWidget *ability_declination_selector::widget() const
  {
    return outer_widget;
  }

  void ability_declination_selector::generate_widget()
  {
    ability_and_declination_layout = new QHBoxLayout;
    setLayout(ability_and_declination_layout);
    std::string ability_name = character::ability_names::ABILITY_NAME.at(_ability.ability);
    if (!_is_ability_editable)
      {
        ability_and_declination_layout->addWidget(label(ability_name));
      }
    else
      {
        ability_selection = new QComboBox();
        ability_selection->addItems(generate_available_abilities());
        ability_selection->setCurrentText(ability_name.c_str());
        ability_selection->setEditable(true);
        ability_and_declination_layout->addWidget(ability_selection);
      }

    if (!character::ability_names::has_declination(_ability.ability))
      return;

    create_declination = new QPushButton(_ability.declination == character::ability_names::ability_declination::NO_DECLINATION
                                         ? "Create declination"
                                         : _ability.declination.c_str());
    create_declination->setEnabled(_is_declination_editable);
    ability_and_declination_layout->addWidget(create_declination);
  }

  void ability_declination_selector::set_ability(detailed_ability ability)
  {
    _ability = ability;
    emit on_ability_selected(ability);
  }

  QStringList ability_declination_selector::generate_available_abilities() const
  {
    QStringList result;
    for (auto ability_e : character::ability_names::ABILITIES)
      result.append(character::ability_names::ABILITY_NAME.at(ability_e).c_str());

    return result;
  }

  QStringList ability_declination_selector::generate_available_declinations() const
  {
    QStringList result;

    if (_ability.declination != character::ability_names::ability_declination::NO_DECLINATION)
      result.append(_ability.declination.c_str());

    for (auto declination: character::ability_names::ability_declination::DECLINATIONS_OF_ABILITY.at(_ability.ability))
      result.append(declination.c_str());

    return result;
  }

}}
