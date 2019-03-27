#pragma once

#include <QWidget>

namespace qt {
  namespace screen {

    class qmainscreen : public QWidget
    {
      Q_OBJECT

    public:
      qmainscreen(QWidget* parent);
    };

  }
}
