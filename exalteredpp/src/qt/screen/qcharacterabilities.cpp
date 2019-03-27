#include "screen/qcharacterabilities.h"

#include <QScrollArea>
#include <QVBoxLayout>
#include "behavioral/name_value_pair.h"
#include "widget/name_value_widget.h"
#include "abilities/ability_names.h"

namespace qt
{
  namespace screen
  {
    qcharacterabilities::qcharacterabilities(QSharedPointer<character::character> character, QWidget* parent)
      : QWidget (parent)
    {
      QWidget* abilities_list = new QWidget;
      QVBoxLayout *v_layout = new QVBoxLayout(this), *inner_layout = new QVBoxLayout;

      v_layout->addWidget(new QLabel("Abilities of " + character->get_name()));

      for (character::ability_name ability_name: character::ABILITY_NAME.keys())
      {
        QWidget* label_widget = new widget::name_value_widget(character->get_ability(ability_name), this);
        inner_layout->addWidget(label_widget);
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
