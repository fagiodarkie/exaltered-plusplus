#pragma once

#include <QWidget>
#include <character.h>

namespace qt {
  namespace screen {
    class qwillpower_virtues_screen : public QWidget
    {
      Q_OBJECT
    public:
      qwillpower_virtues_screen(const std::shared_ptr<character::character> c, QWidget *parent = nullptr);
    };

  }
}
