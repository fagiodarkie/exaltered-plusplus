#include "wizard/chargen/attributes_priority_page.h"
#include "qt/label/interfacelabels.h"
#include "qt/layout/qborderlayout.h"
#include "caste_style.h"

namespace qt {
  namespace wizard {

    using namespace qt::labels;
    using namespace qt::labels::creation_wizard;
    using namespace attribute;

    attributes_priority_page::attributes_priority_page(QWidget* parent)
      : QWidget(parent)
    {
      primary = secondary = tertiary = 0;

      attributes_form = new QFormLayout;
      create_attributes();
      QWidget* central_widget = new QWidget;
      central_widget->setLayout(attributes_form);

      on_next_issued([this](){ chose_all(); });

      layout::QBorderLayout *outer_layout = new layout::QBorderLayout;
      outer_layout->addWidget(_progress_bar, layout::QBorderLayout::North);
      outer_layout->addWidget(central_widget, layout::QBorderLayout::Center);
      outer_layout->addWidget(buttons_layout(), layout::QBorderLayout::South);
      setLayout(outer_layout);
      enable_next();
    }

    void attributes_priority_page::create_attributes()
    {
      primary_select = new QComboBox;
      primary_label = new QLabel(PRIMARY_ATTRIBUTE);
      attributes_form->addRow(primary_label, primary_select);
      connect(primary_select, &QComboBox::currentTextChanged, this, &attributes_priority_page::first_attribute_change);

      secondary_select = new QComboBox;
      secondary_label = new QLabel(SECONDARY_ATTRIBUTE);
      attributes_form->addRow(secondary_label, secondary_select);
      connect(secondary_select, &QComboBox::currentTextChanged, this, &attributes_priority_page::second_attribute_change);

      third_attribute = new QLabel("");
      tertiary_label = new QLabel(TERTIARY_ATTRIBUTE);
      attributes_form->addRow(tertiary_label, third_attribute);

      populate_primary();
      first_attribute_change();
    }

    void attributes_priority_page::populate_primary()
    {
      for (auto category: ATTRIBUTE_CATEGORIES)
        {
          primary_select->addItem(ATTRIBUTE_CATEGORY_NAME.at(category).c_str());
        }
    }

    void attributes_priority_page::set_values(int primary_value, int secondary_value, int tertiary_value)
    {
      primary_label   ->setText(ATTRIBUTE_LABEL_WITH_TOTAL_POINTS(PRIMARY_ATTRIBUTE, primary_value));
      secondary_label ->setText(ATTRIBUTE_LABEL_WITH_TOTAL_POINTS(SECONDARY_ATTRIBUTE, secondary_value));
      tertiary_label  ->setText(ATTRIBUTE_LABEL_WITH_TOTAL_POINTS(TERTIARY_ATTRIBUTE, tertiary_value));
    }

    void attributes_priority_page::first_attribute_change()
    {
      secondary_select->clear();
      QString first_attribute = first_attribute_value();
      for (auto category: ATTRIBUTE_CATEGORIES)
        {
          QString name = ATTRIBUTE_CATEGORY_NAME.at(category).c_str();
          if (name != first_attribute)
            secondary_select->addItem(name);
        }

      second_attribute_change();
    }

    void attributes_priority_page::second_attribute_change()
    {
      QString first_attribute = first_attribute_value(), second_attribute = second_attribute_value();
      for (auto category: ATTRIBUTE_CATEGORIES)
        {
          QString name = ATTRIBUTE_CATEGORY_NAME.at(category).c_str();
          if (name != first_attribute && name != second_attribute)
            third_attribute->setText(name);
        }
    }

    QString attributes_priority_page::first_attribute_value()
    {
      return primary_select->currentText();
    }

    QString attributes_priority_page::second_attribute_value()
    {
      return secondary_select->currentText();
    }

    void attributes_priority_page::chose_all()
    {
      emit attributes_chosen(first_attribute_value(), second_attribute_value(), third_attribute->text());
    }
  }
}
