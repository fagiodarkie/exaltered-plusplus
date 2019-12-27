#include "widget/ability_declination_selector.h"

#include "label/interfacelabels.h"
#include "widget/std_compatible.h"

namespace qt { namespace widget {
  ability_declination_selector::ability_declination_selector(QWidget *parent)
    : QWidget(parent), _ability(character::ability_names::WAR, ""), _is_declination_editable(true), _is_ability_editable(true), outer_widget(new QWidget)
  {
    generate_widget();
  }

  ability_declination_selector::ability_declination_selector(character::ability_names::detailed_ability ability, bool is_ability_editable, bool is_declination_editable, QWidget *parent)
    : QWidget(parent), _ability(ability), _is_declination_editable(true), _is_ability_editable(true), outer_widget(new QWidget)
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

  void ability_declination_selector::signal_taken_abilities(const QList<character::ability_names::detailed_ability> &taken_abilities)
  {
    _prohibited_abilities = taken_abilities;
  }

  void ability_declination_selector::generate_widget()
  {
    // readonly selector
    if (!(_is_ability_editable || _is_declination_editable))
      {
        ability_and_declination_layout = new QVBoxLayout;
        ability_and_declination_layout->addWidget(label(ability_text(_ability)));
        outer_widget->setLayout(ability_and_declination_layout);
        return;
      }

    ability_selection = new QComboBox();
    ability_selection->addItems(generate_available_abilities());

    // pre-fill ability selections
    ability_selection->setCurrentText(ability_text(detailed_ability(_ability.ability)).c_str());

    ability_selection->setEditable(_is_ability_editable);

    ability_and_declination_layout = new QVBoxLayout;
    ability_and_declination_layout->addWidget(ability_selection);

    if (character::ability_names::has_declination(_ability.ability))
      {
        create_declination = new QPushButton("Create declination");
        declination_sublayout = new QHBoxLayout;
        declination_selection = new QComboBox;
        declination_selection->addItems(generate_available_declinations());
      }

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
      {
        // expandable abilities are always available
        if (character::ability_names::has_declination(ability_e))
          {
            result.append(character::ability_names::ABILITY_NAME.at(ability_e).c_str());
            continue;
          }

        // non expandable abilities are available only if not prohibited
        for (auto prohibited: _prohibited_abilities)
          if (prohibited.ability == ability_e)
            continue;

        result.append(character::ability_names::ABILITY_NAME.at(ability_e).c_str());
      }

    return result;
  }

  QStringList ability_declination_selector::generate_available_declinations() const
  {
    QStringList result;

    if (_ability.declination != character::ability_names::ability_declination::NO_DECLINATION)
      result.append(_ability.declination.c_str());

    // cycle available declinations and return those which are not prohibited. Possibly add the selected one.
    for (auto declination: character::ability_names::ability_declination::DECLINATIONS_OF_ABILITY.at(_ability.ability))
      result.append(declination.c_str());

    return result;
  }

  std::string ability_declination_selector::ability_text(detailed_ability ability)
  {
    std::string ability_name = character::ability_names::ABILITY_NAME.at(ability.ability);
    if (ability.declination == character::ability_names::ability_declination::NO_DECLINATION)
      return ability_name;

    return labels::SPECIFY_SUBLABEL(ability_name.c_str(), ability.declination.c_str())
        .toStdString().c_str();
  }
}}
