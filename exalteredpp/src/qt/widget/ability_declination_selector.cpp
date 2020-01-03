#include "widget/ability_declination_selector.h"

#include "label/interfacelabels.h"
#include "widget/std_compatible.h"

namespace qt { namespace widget {
  ability_declination_selector::ability_declination_selector(QWidget *parent)
    : QWidget(parent), _ability(character::ability_names::WAR), _is_declination_editable(true), _is_ability_editable(true)
  {
    generate_widget();
  }

  ability_declination_selector::ability_declination_selector(character::ability_names::detailed_ability ability, bool is_ability_editable, bool is_declination_editable, bool is_favored, QWidget *parent)
    : QWidget(parent), _ability(ability), _is_declination_editable(is_declination_editable), _is_ability_editable(is_ability_editable), _is_favored(is_favored)
  {
    generate_widget();
  }

  ability_declination_selector::ability_declination_selector(std::shared_ptr<character::character> character, QWidget *parent)
    : QWidget(parent), _ability(character::ability_names::WAR), _character_reference(character), _is_declination_editable(true), _is_ability_editable(true), _is_favored(false)
  {
    generate_widget();
  }

  character::ability_names::detailed_ability ability_declination_selector::value() const
  {
    return _ability;
  }

  void ability_declination_selector::repaint(const QList<QWidget*> &widgets_in_layout)
  {
    delete layout();

    ability_and_declination_layout = new QGridLayout;

    for (auto widget: widgets_in_layout)
      {
        if (_is_favored)
          widget->setStyleSheet("font-weight: bold");
        else
          widget->setStyleSheet("font-weight: normal");

        widget->adjustSize();
      }

    if (widgets_in_layout.size() == 2)
      {
        ability_and_declination_layout->addWidget(widgets_in_layout.at(0), 0, 0);
        ability_and_declination_layout->addWidget(widgets_in_layout.at(1), 0, 1);
      }
    else
      {
        ability_and_declination_layout->addWidget(widgets_in_layout.at(0), 0, 0, 1, 2);
      }

    setLayout(ability_and_declination_layout);
  }

  void ability_declination_selector::generate_widget()
  {
    ability_and_declination_layout = new QGridLayout;

    ability_selection = new QComboBox;
    generate_available_abilities();
    ability_selection->setEditable(_is_ability_editable);
    ability_selection->setCurrentText(character::ability_names::ABILITY_NAME.at(_ability.ability).c_str());

    declination_selection = new QComboBox;
    declination_selection->setEditable(_is_declination_editable);
    if (character::ability_names::has_declination(_ability.ability))
      {
        generate_available_declinations();
        declination_selection->setCurrentText(_ability.declination.c_str());
      }

    connect (ability_selection, &QComboBox::editTextChanged, this, &ability_declination_selector::refresh);
    connect (declination_selection, &QComboBox::editTextChanged, this, &ability_declination_selector::update_ability);

    refresh();
  }

  void ability_declination_selector::update_ability()
  {
    _ability.ability = selected_ability();
    if (character::ability_names::has_declination(_ability.ability))
      _ability.declination = declination_selection->currentText().toStdString();
  }

  void ability_declination_selector::refresh()
  {
    update_ability();
    QList<QWidget*> to_display;

    if (_character_reference)
      _is_favored = _character_reference->get_ability(_ability).is_favourite();

    std::string ability_name = character::ability_names::ABILITY_NAME.at(_ability.ability);
    if (!_is_ability_editable)
      {
        to_display.push_back(label(ability_name));
      }
    else
      {
        ability_selection->setCurrentText(ability_name.c_str());
        to_display.push_back(ability_selection);
      }

    if (character::ability_names::has_declination(_ability.ability))
      {
        if (_is_declination_editable)
          {
            generate_available_declinations();
            to_display.push_back(declination_selection);
          }
        else
          {
            to_display.push_back(label(_ability.declination));
          }
      }

    repaint(to_display);
  }

  void ability_declination_selector::set_favored(bool favored)
  {
    _is_favored = favored;
  }

  void ability_declination_selector::set_ability(detailed_ability ability)
  {
    _ability = ability;
    emit on_ability_selected(ability);
  }

  character::ability_names::ability_enum ability_declination_selector::selected_ability() const
  {
    return static_cast<character::ability_names::ability_enum>(ability_selection->currentData().toInt());
  }

  void ability_declination_selector::generate_available_abilities() const
  {
    for (auto ability_e : character::ability_names::ABILITIES)
      ability_selection->addItem(character::ability_names::ABILITY_NAME.at(ability_e).c_str(), ability_e);
  }

  void ability_declination_selector::generate_available_declinations() const
  {
    declination_selection->clear();

    if (_character_reference)
      {
        for (auto ability: _character_reference->get_ability_group(selected_ability()).get_ability_names())
          declination_selection->addItem(ability.declination.c_str());

        return;
      }

    for (auto declination: character::ability_names::ability_declination::DECLINATIONS_OF_ABILITY.at(_ability.ability))
      declination_selection->addItem(declination.c_str());
  }

}}
