#pragma once

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
    };

  }
}
