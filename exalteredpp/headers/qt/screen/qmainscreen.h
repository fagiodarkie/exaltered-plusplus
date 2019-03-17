#pragma once

#include <QLabel>
#include <QWidget>
#include <character.h>

namespace qt
{
  namespace screen
  {
    class qmainscreen : public QWidget
    {
        Q_OBJECT
    public:
        explicit qmainscreen(QSharedPointer<character::character> character, QWidget *parent = nullptr);

    signals:

    public slots:

    private:
      QSharedPointer<character::character> character;
      QLabel character_name_widget;
    };

  }
}
