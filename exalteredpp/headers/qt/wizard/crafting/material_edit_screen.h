#pragma once

#include <QWidget>

#include "equipment/craft/material.h"
#include <QPushButton>

namespace qt
{
  namespace wizard
  {
    class material_edit_screen : public QWidget
    {
      Q_OBJECT
    public:
      explicit material_edit_screen(QWidget *parent = nullptr);

      void with_material(const equipment::craft::material& m);

    signals:
      void save_material(const equipment::craft::material& m);
      void back_issued();

    public slots:

    private:
      equipment::craft::material material;
      QPushButton* back;
    };
  }
}
