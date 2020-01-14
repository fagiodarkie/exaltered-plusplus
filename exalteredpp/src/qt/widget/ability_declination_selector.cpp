#include "widget/ability_declination_selector.h"

#include "label/interfacelabels.h"
#include "widget/std_compatible.h"

namespace qt { namespace widget {
  ability_declination_selector::ability_declination_selector(QWidget *parent)
    : QWidget(parent), _ability(ability::WAR), _is_declination_editable(true), _is_ability_editable(true)
  {
    generate_widget();
  }

  ability_declination_selector::ability_declination_selector(ability::detailed_ability ability, bool is_ability_editable, bool is_declination_editable, bool is_favored, QWidget *parent)
    : QWidget(parent), _ability(ability), _is_declination_editable(is_declination_editable), _is_ability_editable(is_ability_editable), _is_favored(is_favored)
  {
    generate_widget();
  }

  ability_declination_selector::ability_declination_selector(std::shared_ptr<character::character> character, QWidget *parent)
    : QWidget(parent), _ability(ability::WAR), _character_reference(character), _is_declination_editable(true), _is_ability_editable(true), _is_favored(false)
  {
    generate_widget();
  }

  ability::detailed_ability ability_declination_selector::value() const
  {
    return _ability;
  }

  void ability_declination_selector::repaint(const QList<QWidget*> &widgets_in_layout)
  {
    ability_name->hide();
    ability_selection->hide();
    declination_name->hide();
    declination_selection->hide();

    for (auto widget: widgets_in_layout)
      {
        widget->show();
        if (_is_favored)
          widget->setStyleSheet("font-weight: bold");
        else
          widget->setStyleSheet("font-weight: normal");
      }
  }

  void ability_declination_selector::generate_widget()
  {
    ability_and_declination_layout = new QGridLayout;

    ability_name = new QLabel;
    declination_name = new QLabel;

    ability_selection = new QComboBox;
    generate_available_abilities();
    ability_selection->setEnabled(_is_ability_editable);
    ability_selection->setCurrentText(ability::ABILITY_NAME.at(_ability.ability).c_str());

    declination_selection = new QComboBox;
    declination_selection->setEnabled(_is_declination_editable);
    if (ability::has_declination(_ability.ability))
      {
        generate_available_declinations();
      }
    declination_selection->setCurrentText(_ability.declination.c_str());

    ability_and_declination_layout->addWidget(ability_name, 0, 0);
    ability_and_declination_layout->addWidget(declination_name, 0, 1);
    ability_and_declination_layout->addWidget(ability_selection, 1, 0);
    ability_and_declination_layout->addWidget(declination_selection, 1, 1);
    setLayout(ability_and_declination_layout);

    connect (ability_selection, &QComboBox::currentTextChanged, this, &ability_declination_selector::on_ability_change);
    connect (declination_selection, &QComboBox::currentTextChanged, this, &ability_declination_selector::on_declination_change);

    refresh();
  }

  void ability_declination_selector::update_ability()
  {
    if (!_is_ability_editable && !_is_declination_editable)
      return;

    _ability.ability = selected_ability();
    if (ability::has_declination(_ability.ability))
      {
        auto current_declination = declination_selection->currentText().toStdString();
        if (current_declination != ability::ability_declination::NO_DECLINATION
            && !current_declination.empty()
            && (!_character_reference || _character_reference->get_ability_group(_ability.ability).has_ability(current_declination)))
        _ability.declination = current_declination;
      }
    else {
        _ability.declination = ability::ability_declination::NO_DECLINATION;
      }
  }

  void ability_declination_selector::on_ability_change()
  {
    generate_available_declinations();
    refresh();
    emit on_ability_selected(_ability);
  }

  void ability_declination_selector::on_declination_change()
  {
    update_ability();
    emit on_ability_selected(_ability);
  }

  void ability_declination_selector::refresh()
  {
    update_ability();
    QList<QWidget*> to_display;

    if (_character_reference)
      _is_favored = _character_reference->get_ability(_ability).is_favourite();

    std::string ability_name_str = ability::ABILITY_NAME.at(_ability.ability);
    ability_name->setText(ability_name_str.c_str());
    ability_selection->setCurrentText(ability_name_str.c_str());

    if (!_is_ability_editable)
      {
        to_display.push_back(ability_name);
      }
    else
      {
        to_display.push_back(ability_selection);
      }

    if (ability::has_declination(_ability.ability))
      {
        declination_name->setText(_ability.declination.c_str());
        if (_is_declination_editable)
          {
            generate_available_declinations();
            to_display.push_back(declination_selection);
          }
        else
          {
            to_display.push_back(declination_name);
          }
      }

    repaint(to_display);
  }

  void ability_declination_selector::set_favored(bool favored)
  {
    _is_favored = favored;
    refresh();
  }

  void ability_declination_selector::set_ability(detailed_ability ability)
  {
    _ability = ability;
    emit on_ability_selected(ability);
  }

  ability::ability_enum ability_declination_selector::selected_ability() const
  {
    return static_cast<ability::ability_enum>(ability_selection->currentData().toInt());
  }

  void ability_declination_selector::generate_available_abilities() const
  {
    for (auto ability_e : ability::ABILITIES)
      ability_selection->addItem(ability::ABILITY_NAME.at(ability_e).c_str(), ability_e);
  }

  void ability_declination_selector::generate_available_declinations() const
  {
    declination_selection->clear();

    if (_character_reference)
      {
        for (auto ability: _character_reference->get_ability_group(selected_ability()).get_detailed_abilities())
          declination_selection->addItem(ability.declination.c_str());

        return;
      }

    for (auto declination: ability::ability_declination::DECLINATIONS_OF_ABILITY.at(_ability.ability))
      declination_selection->addItem(declination.c_str());
  }

}}
