#pragma once

#include <QWidget>

#include "virtues/virtues.h"

namespace qt {
  namespace wizard {

    using namespace character::virtues;

    class character_creation_virtues_vice : public QWidget
    {
      Q_OBJECT

    public:
      character_creation_virtues_vice(QWidget* parent = nullptr);

    signals:
      void back_issued();
      void virtues_chosen(virtues chosen_virtues);

    private:
      virtues _virtues;
    };
  }
}
