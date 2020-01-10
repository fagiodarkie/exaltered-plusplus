#include "widget/experience_purchase_widget.h"

#include "narrative/experience_defines.h"
#include "attributes/attribute_names.h"
#include "virtues/virtue_names.h"
#include "caste_style.h"

#include "narrative/attribute_purchase.h"
#include "narrative/ability_purchase.h"
#include "narrative/specialisation_purchase.h"
#include "narrative/virtue_purchase.h"
#include "narrative/vice_purchase.h"
#include "narrative/essence_purchase.h"
#include "narrative/willpower_purchase.h"

#include "calculator/experience_purchase_cost_calculator.h"

#include "layout/qborderlayout.h"
#include <QVBoxLayout>

namespace qt { namespace widget {

    using namespace character::narrative;
    using namespace character;

    experience_purchase_widget::experience_purchase_widget(std::shared_ptr<class character> character, QWidget* parent)
      : QDialog(parent), _character(character), available(0)
    {
      setWindowTitle("Purchase");

      attribute_dropdown = new QComboBox;
      virtue_dropdown = new QComboBox;
      purchase_type_dropdown = new QComboBox;
      ability_selector = new widget::ability_declination_selector(_character);
      specialty_freetext = new QLineEdit;
      cost_label = new QLabel("Total cost: gnegne");
      purchase_submit = new QPushButton("Purchase!");
      purchase_submit->setEnabled(false);
      qt::style::foreground(purchase_submit);

      for (auto purchase_type: EXPENSE_TYPES)
        purchase_type_dropdown->addItem(EXPENSE_NAME.at(purchase_type).c_str(), purchase_type);

      for (auto attribute: attribute_names::ATTRIBUTES)
        attribute_dropdown->addItem(attribute_names::ATTRIBUTE_NAME.at(attribute).c_str(), attribute);

      for (auto virtue: virtues::VIRTUE_LIST)
        virtue_dropdown->addItem(virtues::VIRTUE_NAME.at(virtue).c_str(), virtue);

      connect(purchase_type_dropdown, &QComboBox::currentTextChanged, this, &experience_purchase_widget::purchase_type_selected);
      connect(purchase_type_dropdown, &QComboBox::currentTextChanged, this, &experience_purchase_widget::compute_cost_label);
      connect(attribute_dropdown,     &QComboBox::currentTextChanged, this, &experience_purchase_widget::compute_cost_label);
      connect(virtue_dropdown,        &QComboBox::currentTextChanged, this, &experience_purchase_widget::compute_cost_label);
      connect(ability_selector, &widget::ability_declination_selector::on_ability_selected, this, &experience_purchase_widget::compute_cost_label);

      connect(purchase_submit, &QPushButton::clicked, this, &experience_purchase_widget::submit_purchase);

      purchase_type_selected();
    }

    int experience_purchase_widget::selected_purchase_type() const
    {
      return purchase_type_dropdown->currentData().toInt();
    }

    void experience_purchase_widget::set_available_experience(unsigned int experience)
    {
      available = experience;
      compute_cost_label();
    }

    void experience_purchase_widget::purchase_type_selected()
    {
      auto purchase_type = selected_purchase_type();

      QList<QWidget*> widgets_in_list;

      switch (purchase_type)
        {
        case ATTRIBUTE:
          {
            widgets_in_list = { attribute_dropdown };
            break;
          }
        case SPECIALISATION:
          {
            widgets_in_list = { ability_selector, specialty_freetext };
            break;
          }
        case ABILITY:
          {
            widgets_in_list = { ability_selector };
            break;
          }
        case VIRTUE:
          {
            widgets_in_list = { virtue_dropdown };
            break;
          }
        default: { }
        }

      compute_cost_label();
      redraw(widgets_in_list);
    }

    void experience_purchase_widget::submit_purchase()
    {
      emit purchased(compute_purchase());
    }

    void experience_purchase_widget::redraw(const QList<QWidget*> widgets_in_list)
    {
      delete layout();

      QVBoxLayout *list = new QVBoxLayout;
      list->addWidget(purchase_type_dropdown);

      for (auto widget: widgets_in_list)
        {
          list->addWidget(widget);
          widget->adjustSize();
        }

      list->addWidget(cost_label);
      list->setAlignment(Qt::AlignTop | Qt::AlignHCenter);
      QWidget *list_widget = new QWidget;
      list_widget->setLayout(list);
      list_widget->adjustSize();

      QVBoxLayout *buttons = new QVBoxLayout;
      buttons->addWidget(purchase_submit);
      QWidget *buttons_widget = new QWidget;
      buttons_widget->setLayout(buttons);

      layout::QBorderLayout *outer = new layout::QBorderLayout;
      outer->addWidget(buttons_widget, layout::QBorderLayout::South);
      outer->addWidget(list_widget, layout::QBorderLayout::Center);
      setLayout(outer);
    }

    void experience_purchase_widget::compute_cost_label() const
    {
      auto purchase = compute_purchase();
      cost_label->setText(QString("Cost: %1 xp").arg(purchase.cost()));

      validate(purchase.cost());
    }

    unsigned int experience_purchase_widget::compute_cost(narrative::experience_expense_type purchase_type, std::shared_ptr<narrative::abstract_purchase> purchase) const
    {
      return calculator::purchase_cost_calculator::cost_of(purchase_type, purchase)
             .for_who(_character);
    }

    narrative::experience_purchase experience_purchase_widget::compute_purchase() const
    {
      auto purchase_type = selected_purchase_type();
      std::shared_ptr<abstract_purchase> purchase;
      switch (purchase_type)
        {
        case narrative::ATTRIBUTE: {
          auto attribute = selected_attribute();
          purchase = std::make_shared<attribute_purchase>(attribute,_character->get_attribute(attribute) + 1);
          break;
        }
        case narrative::ABILITY: {
          auto ability = selected_ability();
          purchase = std::make_shared<ability_purchase>(ability, _character->get_ability(ability) + 1);
          break;
        }
        case narrative::SPECIALISATION: {
          auto ability = selected_ability().ability;
          auto specialisation = specialty_freetext->text().trimmed().toStdString();
          unsigned int current_value = _character->get_ability_group(ability).has_specialisation(specialisation)
              ? _character->get_ability_group(ability).get_specialisation(specialisation).get_specialisation_value()
              : 0;
          purchase = std::make_shared<specialisation_purchase>(current_value + 1, ability, specialisation);
          break;
        }
        case narrative::VIRTUE: {
          auto virtue = selected_virtue();
          purchase = std::make_shared<virtue_purchase>(_character->get_virtue(virtue).value() + 1, virtue);
          break;
        }
        case narrative::VICE: {
          purchase = std::make_shared<vice_purchase>(_character->get_vice_value() + 1);
          break;
        }
        case narrative::ESSENCE: {
          purchase = std::make_shared<essence_purchase>(_character->get_essence().permanent_essence() + 1);
          break;
        }
        case narrative::WILLPOWER: {
          purchase = std::make_shared<willpower_purchase>(_character->get_willpower().permanent_willpower() + 1);
          break;
        }
        }

      auto purchase_type_enum = static_cast<narrative::experience_expense_type>(purchase_type);
      return narrative::experience_purchase(purchase_type_enum, compute_cost(purchase_type_enum, purchase), purchase);
    }

    attribute_names::attribute experience_purchase_widget::selected_attribute() const
    {
      return static_cast<attribute_names::attribute>(attribute_dropdown->currentData().toInt());
    }

    ability_names::detailed_ability experience_purchase_widget::selected_ability() const
    {
      return ability_selector->value();
    }

    virtues::virtue_enum experience_purchase_widget::selected_virtue() const
    {
      return static_cast<virtues::virtue_enum>(virtue_dropdown->currentData().toInt());
    }

    void experience_purchase_widget::validate(unsigned int cost) const
    {
      auto purchase_type = selected_purchase_type();
      if (cost > available)
        {
          purchase_submit->setEnabled(false);
          return;
        }

      switch (purchase_type)
        {
        case narrative::SPECIALISATION:
          purchase_submit->setEnabled(!specialty_freetext->text().isEmpty());
          break;

        default:
          purchase_submit->setEnabled(true);
        }
    }

} }
