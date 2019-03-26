#include "screen/qcharacterattributes.h"

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
      QVBoxLayout *v_layout = new QVBoxLayout(this);

      for (character::attribute_name attribute_name: character::ATTRIBUTE_NAME.keys())
      {
        v_layout->addWidget(new widget::name_value_widget(character->get_attribute(attribute_name), this));
      }

      setLayout(v_layout);
    }
  }
}
