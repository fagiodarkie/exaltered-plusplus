#include "wizard/character_creation_attribute_points_page.h"

#include "label/interfacelabels.h"
#include "layout/qborderlayout.h"
#include "layout/layout_constants.h"
#include <QFormLayout>
#include <QScrollArea>
#include "invalid_parameter.h"

namespace qt {
  namespace wizard {

    using namespace qt::labels::creation_wizard;
    using namespace qt::labels;
    using character::attribute_names::attribute_category;
    using character::attribute;

    character_creation_attribute_points_page::character_creation_attribute_points_page(QWidget *parent)
      : QWidget(parent)
    {
      generate_group_labels();
      generate_attribute_labels();

      QVBoxLayout *categories_layout = new QVBoxLayout;
      for (auto category: character::attribute_names::ATTRIBUTE_CATEGORIES)
        {
          categories_layout->addWidget(generate_category_group(category));
        }
      QWidget* categories = new QWidget;
      categories->setLayout(categories_layout);

      connect(this, &character_creation_attribute_points_page::total_changed, this, &character_creation_attribute_points_page::rethink_button_enable);

      QHBoxLayout* buttons_layout = new QHBoxLayout;
      next_page = new QPushButton(NEXT_LABEL);
      cancel = new QPushButton(CANCEL_LABEL);
      buttons_layout->addWidget(cancel);
      buttons_layout->addWidget(next_page);

      next_page->setEnabled(false);
      connect(next_page, &QPushButton::clicked, this, &character_creation_attribute_points_page::chose_points);
      connect(cancel, &QPushButton::clicked, this, &character_creation_attribute_points_page::back_issued);

      QWidget* buttons = new QWidget;
      buttons->setLayout(buttons_layout);

      layout::QBorderLayout *outer_layout = new layout::QBorderLayout;
      QScrollArea *scroll_categories = new QScrollArea;
      scroll_categories->setWidget(categories);
      outer_layout->addWidget(scroll_categories, layout::QBorderLayout::Center);
      outer_layout->addWidget(buttons, layout::QBorderLayout::South);

      setLayout(outer_layout);
    }

    void character_creation_attribute_points_page::set_total_points(QMap<attribute_category, unsigned int> points_per_category)
    {
      this->points_per_category = points_per_category;
      generate_group_labels();
    }

    QPushButton* character_creation_attribute_points_page::generate_add_button()
    {
      QPushButton* button = new QPushButton("+");
      button->setFixedSize(layout::SQUARE_BUTTON_STD_SIZE);

      connect(button, &QPushButton::clicked, this, &character_creation_attribute_points_page::increase_attribute);

      return button;
    }

    QPushButton* character_creation_attribute_points_page::generate_subtract_button()
    {
      QPushButton* button = new QPushButton("-");
      button->setFixedSize(layout::SQUARE_BUTTON_STD_SIZE);

      connect(button, &QPushButton::clicked, this, &character_creation_attribute_points_page::decrease_attribute);

      button->setEnabled(false);
      return button;
    }

    void character_creation_attribute_points_page::increase_attribute()
    {
      character::attribute_names::attribute attr = retrieve_attribute_from_call();
      character::attribute new_attribute(chosen_attributes[attr].get_name(), chosen_attributes[attr] + 1);
      chosen_attributes[attr] = new_attribute;
      emit total_changed(character::attribute_names::CATEGORY_OF_ATTRIBUTE(attr));
    }

    void character_creation_attribute_points_page::decrease_attribute()
    {
      character::attribute_names::attribute attr = retrieve_attribute_from_call();
      character::attribute new_attribute(chosen_attributes[attr].get_name(), chosen_attributes[attr] - 1);
      chosen_attributes[attr] = new_attribute;
      emit total_changed(character::attribute_names::CATEGORY_OF_ATTRIBUTE(attr));
    }

    character::attribute_names::attribute character_creation_attribute_points_page::retrieve_attribute_from_call()
    {
      QObject* event_sender = sender();

      auto attribute_iterator = std::find_if(character::attribute_names::ATTRIBUTES.begin(), character::attribute_names::ATTRIBUTES.end(),
                                             [this, event_sender](character::attribute_names::attribute attr) -> bool { return increase_buttons_by_attribute[attr] == event_sender; });

      if (attribute_iterator == character::attribute_names::ATTRIBUTES.end())
        attribute_iterator = std::find_if(character::attribute_names::ATTRIBUTES.begin(), character::attribute_names::ATTRIBUTES.end(),
                                             [this, event_sender](character::attribute_names::attribute attr) -> bool { return decrease_buttons_by_attribute[attr] == event_sender; });

      if (attribute_iterator == character::attribute_names::ATTRIBUTES.end())
        throw new exception::invalid_parameter();

      return *attribute_iterator;
    }

    void character_creation_attribute_points_page::rethink_button_enable(attribute_category category)
    {
      unsigned int current_points = total_points_for_category(category);

      auto attributes_in_category = character::attribute_names::ATTRIBUTES_BY_CATEGORY[category];

      bool able_to_increase = current_points < max_points_for_category(category);

      for (auto attribute_type: attributes_in_category)
        {
          decrease_buttons_by_attribute[attribute_type]->setEnabled(chosen_attributes[attribute_type] > 1);
          increase_buttons_by_attribute[attribute_type]->setEnabled(able_to_increase
                && chosen_attributes[attribute_type] < 5);
        }

      bool all_categories_have_right_points = true;
      for (auto generic_category: character::attribute_names::ATTRIBUTE_CATEGORIES)
        {
          if (total_points_for_category(generic_category) != max_points_for_category(generic_category))
            {
              all_categories_have_right_points = false;
              break;
            }
        }
      next_page->setEnabled(all_categories_have_right_points);

      generate_attribute_labels_for_category(category);
    }

    void character_creation_attribute_points_page::generate_group_labels()
    {
      if (group_label_by_category.isEmpty())
        {
          for (auto category:character::attribute_names::ATTRIBUTE_CATEGORIES)
            group_label_by_category[category] = new QGroupBox;
        }

      for (auto category:character::attribute_names::ATTRIBUTE_CATEGORIES)
        group_label_by_category[category]->setTitle(
              qt::labels::creation_wizard::ATTRIBUTE_LABEL_WITH_TOTAL_POINTS(character::attribute_names::ATTRIBUTE_CATEGORY_NAME[category],
                                                                 static_cast<int>(points_per_category[category])));
    }

    void character_creation_attribute_points_page::generate_attribute_labels()
    {
      for (auto category:character::attribute_names::ATTRIBUTE_CATEGORIES)
        generate_attribute_labels_for_category(category);
    }

    void character_creation_attribute_points_page::generate_attribute_labels_for_category(attribute_category category)
    {
      for (auto attribute:character::attribute_names::ATTRIBUTES_BY_CATEGORY[category])
        {
          if (!label_by_attribute.contains(attribute))
            label_by_attribute[attribute] = new QLabel();
        }

      for (auto attribute:character::attribute_names::ATTRIBUTES_BY_CATEGORY[category])
        label_by_attribute[attribute]->setText(
              qt::labels::creation_wizard::ATTRIBUTE_WITH_POINTS(character::attribute_names::ATTRIBUTE_NAME[attribute],
                                                                 static_cast<int>(chosen_attributes[attribute])));
    }

    QWidget* character_creation_attribute_points_page::generate_category_group(attribute_category category)
    {
      QGroupBox* category_box = group_label_by_category[category];

      QFormLayout* form = new QFormLayout;

      for (auto attribute : character::attribute_names::ATTRIBUTES_BY_CATEGORY[category])
        {
          auto add_button = generate_add_button();
          auto subtract_button = generate_subtract_button();

          increase_buttons_by_category[category].append(add_button);
          decrease_buttons_by_category[category].append(subtract_button);

          increase_buttons_by_attribute[attribute] = add_button;
          decrease_buttons_by_attribute[attribute] = subtract_button;

          form->addRow(label_by_attribute[attribute], generate_plusminus_buttons_widget(add_button, subtract_button));
        }

      category_box->setLayout(form);

      return category_box;
    }

    void character_creation_attribute_points_page::set_current_attributes(const character::attributes &attributes)
    {
      chosen_attributes = attributes;
      generate_attribute_labels();
    }

    QWidget* character_creation_attribute_points_page::generate_plusminus_buttons_widget(QPushButton* add, QPushButton* subtract)
    {
      QHBoxLayout* hlayout = new QHBoxLayout;
      QWidget *result = new QWidget;

      hlayout->addWidget(add);
      hlayout->addWidget(subtract);

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
      for (auto attribute : character::attribute_names::ATTRIBUTES_BY_CATEGORY[category])
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
