#pragma once

#include <QMainWindow>

#include "screen/qloadcharacterscreen.h"

using namespace qt::screen;

class ExalteredApp : public QWidget
{
  Q_OBJECT

  public:
    ExalteredApp(QWidget *parent = nullptr);
    ~ExalteredApp();

private:
    void initLoadScreen();
    QLoadCharacterScreen* loadCharacterScreen;
};
