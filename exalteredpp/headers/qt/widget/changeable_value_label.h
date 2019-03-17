#include <QLabel>

#pragma once

namespace qt
{
  namespace widget
  {
    class changeable_value_label : public QLabel
    {
      Q_OBJECT
    public:
      changeable_value_label(const QString& label_text, QFunctionPointer on_tap);
      void set_reaction(QFunctionPointer on_tap);

    signals:
      void clicked();

    protected:
      void mousePressEvent(QMouseEvent* ev) override;
      void on_click();
      QFunctionPointer on_click_function;
    };
  }
}
