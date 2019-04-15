#include "screen/qcharacterattributes.h"

#include <QScrollArea>
#include <QVBoxLayout>
#include "behavioral/name_value_pair.h"
#include "widget/name_value_widget.h"
#include "attributes/attribute_names.h"

namespace qt
{
  namespace screen
  {
    qcharacterattributes::qcharacterattributes(QSharedPointer<character::character> character, QWidget* parent)
      : QWidget (parent)
    {
      QWidget* attributes_list = new QWidget;
      QVBoxLayout *v_layout = new QVBoxLayout(this), *inner_layout = new QVBoxLayout;

      v_layout->addWidget(new QLabel("Attributes of " + character->get_name()));

      for (character::attribute_names::attribute_name attribute_name: character::attribute_names::ATTRIBUTE_NAME.keys())
      {
        inner_layout->addWidget(new widget::name_value_widget(character->get_attribute(attribute_name), this));
      }

      attributes_list->setLayout(inner_layout);

      QScrollArea *scroll_area = new QScrollArea;
      scroll_area->setWidgetResizable(true);
      scroll_area->setWidget(attributes_list);

      v_layout->addWidget(scroll_area);

      setLayout(v_layout);
    }
  }
}
