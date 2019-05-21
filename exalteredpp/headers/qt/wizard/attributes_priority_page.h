#pragma once

#include <QComboBox>
#include <QFormLayout>
#include <QLabel>
#include <QPushButton>
#include <QWidget>
#include "attributes/attribute_names.h"

namespace qt {
  namespace wizard {

    class attributes_priority_page : public QWidget
    {
      Q_OBJECT

    public:
      attributes_priority_page(QWidget *parent = nullptr);

    signals:
      void attributes_chosen(QString primary_attribute, QString secondary_attribute, QString tertiary_attribute);
      void back_issued();

    private:
      void check_form();
      void chose_all();

      void create_attributes();
      void first_attribute_change();
      void second_attribute_change();
      QString first_attribute_value();
      QString second_attribute_value();

      QComboBox *primary_select, *secondary_select;
      QLabel *third_attribute;
      QPushButton *next_page, *cancel;
      QFormLayout *attributes_form;
    };
  }
}
