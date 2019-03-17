#include "widget/changeable_value_label.h"


namespace qt
{
  namespace widget
  {
    changeable_value_label::changeable_value_label(const QString& text, QFunctionPointer on_tap)
      : QLabel(text), on_click_function(on_tap)
    {
      connect(this, &changeable_value_label::clicked, this, &changeable_value_label::on_click);
    }

    void changeable_value_label::set_reaction(QFunctionPointer on_tap)
    {
      on_click_function = on_tap;
    }

    void changeable_value_label::on_click()
    {
      on_click_function();
    }

    void changeable_value_label::mousePressEvent(QMouseEvent*)
    {
      emit clicked();
    }
  }
}
