#include "screen/qcharacterattributes.h"

#include <QFormLayout>
#include <QGroupBox>
#include <QScrollArea>
#include <QVBoxLayout>
#include "behavioral/name_value_pair.h"
#include "widget/name_value_widget.h"
#include "attributes/attribute_names.h"

namespace qt
{
  namespace screen
  {
    qcharacterattributes::qcharacterattributes(std::shared_ptr<character::character> character, QWidget* parent)
      : QWidget (parent)
    {
      QWidget* attributes_list = new QWidget;
      QVBoxLayout *v_layout = new QVBoxLayout(this), *inner_layout = new QVBoxLayout;

      v_layout->addWidget(new QLabel(QString("Attributes of ") + character->get_name().c_str()));

      for (auto attribute_category: attribute::ATTRIBUTE_CATEGORIES)
        {
          QGroupBox *attribute_category_group = new QGroupBox(attribute::ATTRIBUTE_CATEGORY_NAME.at(attribute_category).c_str());
          QFormLayout *attribute_form = new QFormLayout;
          for (auto attribute_name: attribute::ATTRIBUTES_BY_CATEGORY.at(attribute_category))
          {
              attribute_form->addRow(attribute::ATTRIBUTE_NAME.at(attribute_name).c_str(),
                                     new QLabel(character->get_attribute(attribute_name).get_value().c_str()));
          }
          attribute_category_group->setLayout(attribute_form);
          inner_layout->addWidget(attribute_category_group);
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
