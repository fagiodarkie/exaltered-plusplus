#include "wizard/attributes_priority_page.h"
#include "qt/label/interfacelabels.h"
#include "qt/layout/qborderlayout.h"

namespace qt {
  namespace wizard {

    using namespace qt::labels;
    using namespace qt::labels::creation_wizard;
    using namespace character::attribute_names;

    attributes_priority_page::attributes_priority_page(QWidget* parent)
      : QWidget(parent)
    {
      attributes_form = new QFormLayout;
      create_attributes();
      QWidget* central_widget = new QWidget;
      central_widget->setLayout(attributes_form);

      next_page = new QPushButton(NEXT_LABEL);
      cancel = new QPushButton(CANCEL_LABEL);

      connect(next_page, &QPushButton::clicked, this, &attributes_priority_page::chose_all);
      connect(cancel, &QPushButton::clicked, this, &attributes_priority_page::back_issued);

      QWidget* buttons = new QWidget;
      QHBoxLayout* buttons_layout = new QHBoxLayout;
      buttons_layout->addWidget(cancel);
      buttons_layout->addWidget(next_page);
      buttons->setLayout(buttons_layout);

      layout::QBorderLayout *outer_layout = new layout::QBorderLayout;
      outer_layout->addWidget(central_widget, layout::QBorderLayout::Center);
      outer_layout->addWidget(buttons, layout::QBorderLayout::South);
      setLayout(outer_layout);
    }

    void attributes_priority_page::create_attributes()
    {
      primary_select = new QComboBox;
      for (auto category: ATTRIBUTE_CATEGORY_NAME.keys())
        {
          primary_select->addItem(ATTRIBUTE_CATEGORY_NAME[category]);
        }
      attributes_form->addRow(new QLabel(PRIMARY_ATTRIBUTE), primary_select);

      connect(primary_select, &QComboBox::currentTextChanged, this, &attributes_priority_page::first_attribute_change);

      secondary_select = new QComboBox;
      attributes_form->addRow(new QLabel(SECONDARY_ATTRIBUTE), secondary_select);
      connect(secondary_select, &QComboBox::currentTextChanged, this, &attributes_priority_page::second_attribute_change);

      third_attribute = new QLabel("");
      attributes_form->addRow(new QLabel(TERTIARY_ATTRIBUTE), third_attribute);

      first_attribute_change();
    }

    void attributes_priority_page::first_attribute_change()
    {
      secondary_select->clear();
      QString first_attribute = first_attribute_value();
      for (auto category: ATTRIBUTE_CATEGORY_NAME.keys())
        {
          QString name = ATTRIBUTE_CATEGORY_NAME[category];
          if (name != first_attribute)
            secondary_select->addItem(name);
        }

      second_attribute_change();
    }

    void attributes_priority_page::second_attribute_change()
    {
      QString first_attribute = first_attribute_value(), second_attribute = second_attribute_value();
      for (auto category: ATTRIBUTE_CATEGORY_NAME.keys())
        {
          QString name = ATTRIBUTE_CATEGORY_NAME[category];
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
