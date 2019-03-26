#pragma once

#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>
#include "behavioral/name_value_pair.h"

namespace qt {
  namespace widget {
    class name_value_widget : public QWidget
    {
    public:
      name_value_widget(const model::name_value_pair& name_value, QWidget* parent = nullptr);
    };
  }
}
