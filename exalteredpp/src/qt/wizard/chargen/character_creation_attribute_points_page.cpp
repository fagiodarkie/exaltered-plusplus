#include "wizard/chargen/character_creation_attribute_points_page.h"

#include "label/interfacelabels.h"
#include "layout/qborderlayout.h"
#include "layout/layout_constants.h"
#include <QFormLayout>
#include <QScrollArea>
#include "invalid_parameter.h"
#include "caste_style.h"
#include "attributes/attribute_names.h"

namespace qt {
  namespace wizard {

    using namespace qt::labels::creation_wizard;
    using namespace qt::labels;
    using attribute::attribute_category;
    using attribute::attribute_enum;

    const QString character_creation_attribute_points_page::ATTRIBUTE = "ATTRIBUTE";

    character_creation_attribute_points_page::character_creation_attribute_points_page(QWidget *parent)
      : QWidget(parent)
    {
      generate_group_labels();
      generate_attribute_labels();

      QVBoxLayout *categories_layout = new QVBoxLayout;
      for (auto category: attribute::ATTRIBUTE_CATEGORIES)
        {
          categories_layout->addWidget(generate_category_group(category));
        }
      QWidget* categories = new QWidget;
      categories->setLayout(categories_layout);

      connect(this, &character_creation_attribute_points_page::total_changed, this, &character_creation_attribute_points_page::rethink_button_enable);
      connect(this, &character_creation_attribute_points_page::total_changed, this, &character_creation_attribute_points_page::generate_group_labels);

      on_next_issued([this]() {chose_points();});

      layout::QBorderLayout *outer_layout = new layout::QBorderLayout;
      QScrollArea *scroll_categories = new QScrollArea;
      scroll_categories->setWidget(categories);
      outer_layout->addWidget(_progress_bar, layout::QBorderLayout::North);
      outer_layout->addWidget(scroll_categories, layout::QBorderLayout::Center);
      outer_layout->addWidget(buttons_layout(), layout::QBorderLayout::South);

      setLayout(outer_layout);
    }

    void character_creation_attribute_points_page::set_total_points(QMap<attribute_category, unsigned int> points_per_category)
    {
      this->points_per_category = points_per_category;
      generate_group_labels();
      generate_group_labels();
      rethink_button_enable(attribute::SOCIAL);
      rethink_button_enable(attribute::PHYSICAL);
      rethink_button_enable(attribute::MENTAL);
    }

    QPushButton* character_creation_attribute_points_page::generate_add_button(attribute_enum attribute)
    {
      QPushButton* button = new QPushButton("+");
      button->setFixedSize(layout::SQUARE_BUTTON_STD_SIZE);
      button->setProperty(ATTRIBUTE.toStdString().c_str(), (int)attribute);

      connect(button, &QPushButton::clicked, this, &character_creation_attribute_points_page::increase_attribute);

      return button;
    }

    QPushButton* character_creation_attribute_points_page::generate_subtract_button(attribute_enum attribute)
    {
      QPushButton* button = new QPushButton("-");
      button->setFixedSize(layout::SQUARE_BUTTON_STD_SIZE);
      button->setProperty(ATTRIBUTE.toStdString().c_str(), (int)attribute);

      connect(button, &QPushButton::clicked, this, &character_creation_attribute_points_page::decrease_attribute);

      button->setEnabled(false);
      return button;
    }

    void character_creation_attribute_points_page::increase_attribute()
    {
      auto attr = retrieve_attribute_from_call();
      ++chosen_attributes[attr];
      emit total_changed(attribute::CATEGORY_OF_ATTRIBUTE(attr));
    }

    void character_creation_attribute_points_page::decrease_attribute()
    {
      attribute_enum attr = retrieve_attribute_from_call();
      --chosen_attributes[attr];
      emit total_changed(attribute::CATEGORY_OF_ATTRIBUTE(attr));
    }

    attribute_enum character_creation_attribute_points_page::retrieve_attribute_from_call()
    {
      QObject* event_sender = sender();

      return static_cast<attribute_enum>(event_sender->property(ATTRIBUTE.toStdString().c_str()).toInt());
    }

    void character_creation_attribute_points_page::rethink_button_enable(attribute_category category)
    {
      unsigned int current_points = total_points_for_category(category);

      auto attributes_in_category = attribute::ATTRIBUTES_BY_CATEGORY.at(category);

      bool able_to_increase = current_points < max_points_for_category(category);

      for (auto attributeype: attributes_in_category)
        {
          decrease_buttons_by_attribute[attributeype]->setEnabled(chosen_attributes[attributeype] > 1);
          increase_buttons_by_attribute[attributeype]->setEnabled(able_to_increase
                && chosen_attributes[attributeype] < 5);
        }

      bool all_categories_have_right_points = true;
      for (auto generic_category: attribute::ATTRIBUTE_CATEGORIES)
        {
          if (total_points_for_category(generic_category) != max_points_for_category(generic_category))
            {
              all_categories_have_right_points = false;
              break;
            }
        }
      enable_next(all_categories_have_right_points);

      generate_attribute_labels_for_category(category);
    }

    void character_creation_attribute_points_page::generate_group_labels()
    {
      if (group_label_by_category.isEmpty())
        {
          for (auto category:attribute::ATTRIBUTE_CATEGORIES)
            group_label_by_category[category] = new QGroupBox;
        }

      for (auto category:attribute::ATTRIBUTE_CATEGORIES)
        {
          int current_category_point = 0;
          if (!chosen_attributes.empty())
            {
              for (auto attribute: attribute::ATTRIBUTES_BY_CATEGORY.at(category))
                current_category_point += (chosen_attributes.at(attribute) > 0 ? chosen_attributes.at(attribute) - 1 : 0);
            }

          group_label_by_category[category]->setTitle(
              qt::labels::creation_wizard::ATTRIBUTE_LABEL_WITH_TOTAL_POINTS(attribute::ATTRIBUTE_CATEGORY_NAME.at(category).c_str(),
                                                                 current_category_point,
                                                                 static_cast<int>(points_per_category[category])));
        }
    }

    void character_creation_attribute_points_page::generate_attribute_labels()
    {
      for (auto category:attribute::ATTRIBUTE_CATEGORIES)
        generate_attribute_labels_for_category(category);
    }

    void character_creation_attribute_points_page::generate_attribute_labels_for_category(attribute_category category)
    {
      int max_width = 0;
      for (auto attribute:attribute::ATTRIBUTES_BY_CATEGORY.at(category))
        {
          auto text = qt::labels::creation_wizard::ATTRIBUTE_WITH_POINTS(attribute::ATTRIBUTE_NAME.at(attribute).c_str(),
                                                                         static_cast<int>(chosen_attributes[attribute]));
          if (!label_by_attribute.contains(attribute))
            {
              label_by_attribute[attribute] = new QLabel(text);
              label_by_attribute[attribute]->setFixedHeight(layout::SQUARE_BUTTON_STD_SIZE.height());
              label_by_attribute[attribute]->setAlignment(Qt::AlignVCenter);
            }
          else
            label_by_attribute[attribute]->setText(text);

          max_width = label_by_attribute[attribute]->width() > max_width ? label_by_attribute[attribute]->width() : max_width;
        }
    }

    QWidget* character_creation_attribute_points_page::generate_category_group(attribute_category category)
    {
      QGroupBox* category_box = group_label_by_category[category];

      QGridLayout* form = new QGridLayout;

      int row = 0;
      for (auto attribute : attribute::ATTRIBUTES_BY_CATEGORY.at(category))
        {
          auto add_button = generate_add_button(attribute);
          auto subtract_button = generate_subtract_button(attribute);

          increase_buttons_by_category[category].append(add_button);
          decrease_buttons_by_category[category].append(subtract_button);

          increase_buttons_by_attribute[attribute] = add_button;
          decrease_buttons_by_attribute[attribute] = subtract_button;

          auto buttons = generate_plusminus_buttons_widget(add_button, subtract_button);
          form->addWidget(label_by_attribute[attribute], row, 0, 1, 2);
          form->addWidget(buttons, row, 2, 1, 1);
          ++row;
        }

      category_box->setLayout(form);

      return category_box;
    }

    void character_creation_attribute_points_page::set_current_attributes(const attribute::attributes &attributes)
    {
      chosen_attributes = attributes;
      generate_attribute_labels();
      generate_group_labels();
      rethink_button_enable(attribute::SOCIAL);
      rethink_button_enable(attribute::PHYSICAL);
      rethink_button_enable(attribute::MENTAL);
    }

    QWidget* character_creation_attribute_points_page::generate_plusminus_buttons_widget(QPushButton* add, QPushButton* subtract)
    {
      QHBoxLayout* hlayout = new QHBoxLayout;
      QWidget *result = new QWidget;

      hlayout->addWidget(subtract);
      hlayout->addWidget(add);

      result->setLayout(hlayout);

      return result;
    }

    void character_creation_attribute_points_page::chose_points()
    {
      emit attribute_points_chosen(chosen_attributes);
    }

    unsigned int character_creation_attribute_points_page::total_points_for_category(attribute_category category)
    {
      int result = 0;
      for (auto attribute : attribute::ATTRIBUTES_BY_CATEGORY.at(category))
        {
          result += chosen_attributes[attribute];
        }

      return static_cast<unsigned int>(result);
    }

    unsigned int character_creation_attribute_points_page::max_points_for_category(attribute_category category)
    {
      return points_per_category[category] + 3;
    }
  }
}
