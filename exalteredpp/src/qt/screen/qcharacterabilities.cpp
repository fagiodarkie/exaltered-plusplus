#include "screen/qcharacterabilities.h"

#include <QScrollArea>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QFormLayout>
#include "widget/std_compatible.h"
#include "behavioral/name_value_pair.h"
#include "widget/name_value_widget.h"
#include "abilities/ability.h"

namespace qt
{
  namespace screen
  {
    qcharacterabilities::qcharacterabilities(std::shared_ptr<character::character> character, QWidget* parent)
      : QWidget (parent)
    {
      QWidget* abilities_list = new QWidget;
      QVBoxLayout *v_layout = new QVBoxLayout(this), *inner_layout = new QVBoxLayout;

      v_layout->addWidget(label("Abilities of " + character->get_name()));

      for (auto category: ability::ABILITY_CATEGORIES)
        {
          QGroupBox *category_group = new QGroupBox(ability::ABILITY_CATEGORY_NAMES.at(category).c_str());
          QFormLayout *category_form = new QFormLayout;
          for (auto ability_name: ability::ABILITIES_IN_CATEGORY.at(category))
          {
            for (ability::ability ability : character->get_ability_group(ability_name).get_abilities())
              {
                category_form->addRow(ability.get_name().c_str(), new QLabel(QString::number(ability.get_ability_value())));
              }
          }
          category_group->setLayout(category_form);
          inner_layout->addWidget(category_group);
        }

      abilities_list->setLayout(inner_layout);

      QScrollArea *scroll_area = new QScrollArea;
      scroll_area->setWidgetResizable(true);
      scroll_area->setWidget(abilities_list);

      v_layout->addWidget(scroll_area);

      setLayout(v_layout);
    }
  }
}
