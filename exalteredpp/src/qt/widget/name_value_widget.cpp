#include "widget/name_value_widget.h"

namespace qt {
  namespace widget {
    name_value_widget::name_value_widget(const model::name_value_pair& name_value, QWidget* parent)
      : QWidget(parent)
    {
      QHBoxLayout *layout = new QHBoxLayout(this);
      layout->addWidget(new QLabel(name_value.get_name()));
      layout->addWidget(new QLabel(name_value.get_value()));
      setLayout(layout);
    }
  }
}
