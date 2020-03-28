#ifndef LAYOUT_HELPER_FACTORIES_H
#define LAYOUT_HELPER_FACTORIES_H

#include <QWidget>
#include <QHBoxLayout>

namespace qt {
  namespace layout {

    static QWidget* horizontal_couple(QWidget* left, QWidget* right, QWidget* parent = nullptr)
    {
      QHBoxLayout *layout = new QHBoxLayout;
      layout->addWidget(left);
      layout->addWidget(right);
      QWidget *result = new QWidget(parent);
      result->setLayout(layout);
      return result;
    }

  }
}

#endif // LAYOUT_HELPER_FACTORIES_H
