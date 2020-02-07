#pragma once
#include <QLabel>
#include <QGroupBox>
#include <QPushButton>
#include <QWidget>
#include <QMap>
#include "attributes/attributes.h"
#include "attributes/attribute_names.h"
#include "widget/with_progress_bar.h"
#include "widget/with_next_continue_buttons.h"


namespace qt {
  namespace wizard {

    class character_creation_attribute_points_page : public QWidget, public widget::with_progress_bar, public widget::with_next_back_buttons
    {
      Q_OBJECT

    public:
      explicit character_creation_attribute_points_page(QWidget *parent = nullptr);

      void set_total_points(QMap<attribute::attribute_category, unsigned int> points_per_category);
      void set_current_attributes(const attribute::attributes& attribute);

    signals:
      void attribute_points_chosen(attribute::attributes& chosen_attributes);
      void total_changed(attribute::attribute_category category);

    private slots:
      void increase_attribute();
      void decrease_attribute();


    private:
      attribute::attributes chosen_attributes;

      QMap<attribute::attribute_category, unsigned int> points_per_category;

      QMap<attribute::attribute_category, QGroupBox*> group_label_by_category;
      QMap<attribute::attribute_category, QList<QPushButton*>> increase_buttons_by_category, decrease_buttons_by_category;

      QMap<attribute::attribute_enum, QLabel*> label_by_attribute;
      QMap<attribute::attribute_enum, QPushButton*> increase_buttons_by_attribute, decrease_buttons_by_attribute;

      unsigned int total_points_for_category(attribute::attribute_category att_category);
      unsigned int max_points_for_category(attribute::attribute_category att_category);

      QPushButton* generate_add_button(attribute::attribute_enum attribute);
      QPushButton* generate_subtract_button(attribute::attribute_enum attribute);

      void chose_points();
      void generate_group_labels();
      void generate_attribute_labels();
      void generate_attribute_labels_for_category(attribute::attribute_category category);
      attribute::attribute_enum retrieve_attribute_from_call();

      void rethink_button_enable(attribute::attribute_category category);

      QWidget* generate_category_group(attribute::attribute_category category);
      QWidget* generate_plusminus_buttons_widget(QPushButton* add, QPushButton* subtract);

      const static QString ATTRIBUTE;
    };
  }
}
