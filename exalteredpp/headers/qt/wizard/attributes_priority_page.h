#pragma once

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
      void attributes_chosen(QString primary_attribute, QString secondary_attribute);
      void back_issued();

    private:
      void check_form();
      void chose_all();
    };
  }
}
