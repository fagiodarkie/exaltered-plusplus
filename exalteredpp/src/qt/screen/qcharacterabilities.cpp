#include "screen/qcharacterabilities.h"

#include <QScrollArea>
#include <QVBoxLayout>
#include "widget/std_compatible.h"
#include "behavioral/name_value_pair.h"
#include "widget/name_value_widget.h"
#include "abilities/ability_names.h"

namespace qt
{
  namespace screen
  {
    qcharacterabilities::qcharacterabilities(character::character *character, QWidget* parent)
      : QWidget (parent)
    {
      QWidget* abilities_list = new QWidget;
      QVBoxLayout *v_layout = new QVBoxLayout(this), *inner_layout = new QVBoxLayout;

      v_layout->addWidget(label("Abilities of " + character->get_name()));

      for (auto ability_name: character::ability_names::ABILITIES)
      {
        for (character::ability ability : character->get_ability_group(ability_name).get_abilities())
          {
            QWidget* label_widget = new widget::name_value_widget(ability, this);
            inner_layout->addWidget(label_widget);
          }
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
