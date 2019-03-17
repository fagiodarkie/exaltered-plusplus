#pragma once

#include <QMainWindow>

#include "screen/qloadcharacterscreen.h"
#include "navigation/main_screen_navigation_logic.h"

using namespace qt::screen;

class ExalteredApp : public qt::main_screen_navigation_logic
{
  Q_OBJECT

  public:
    ExalteredApp(QWidget *parent = nullptr);
    ~ExalteredApp();

};
