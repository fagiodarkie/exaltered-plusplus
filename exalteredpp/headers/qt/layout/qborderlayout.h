#pragma once

#include <QLayout>

/**
 * DISCLAIMER
 *
 * The following class was taken from the BorderLayout tutorial provided by Qt.
 * Find the complete tutorial here: https://doc.qt.io/qt-5/qtwidgets-layouts-borderlayout-example.html
 *
 * The developer doesn't claim ownership of any part of this code.
 */

namespace qt {
  namespace layout {
    class QBorderLayout : public QLayout
    {
    public:
      enum Position { West, North, South, East, Center };

      explicit QBorderLayout(QWidget *parent, int margin = 0, int spacing = -1);
      QBorderLayout(int spacing = -1);
      ~QBorderLayout() override;

      void addItem(QLayoutItem *item) override;
      void addWidget(QWidget *widget, Position position);
      Qt::Orientations expandingDirections() const override;
      bool hasHeightForWidth() const override;
      int count() const override;
      QLayoutItem *itemAt(int index) const override;
      QSize minimumSize() const override;
      void setGeometry(const QRect &rect) override;
      QSize sizeHint() const override;
      QLayoutItem *takeAt(int index) override;

      void add(QLayoutItem *item, Position position);

    private:
      struct ItemWrapper
      {
        ItemWrapper(QLayoutItem *i, Position p) {
          item = i;
          position = p;
        }

        QLayoutItem *item;
        Position position;
      };

      enum SizeType { MinimumSize, SizeHint };
      QSize calculateSize(SizeType sizeType) const;

      QList<ItemWrapper *> list;    };
  }
}

