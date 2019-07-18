#include "widget/name_value_widget.h"
#include "widget/std_compatible.h"

namespace qt {
  namespace widget {
    name_value_widget::name_value_widget(const model::name_value_pair& name_value, QWidget* parent)
      : QWidget(parent)
    {
      QHBoxLayout *layout = new QHBoxLayout(this);
      layout->addWidget(label(name_value.get_name()));
      layout->addWidget(label(name_value.get_value()));
      setLayout(layout);
    }
  }
}
