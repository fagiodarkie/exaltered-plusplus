#include "qt/exalteredapp.h"
#include <QApplication>

#include "dependencies.h"

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  ExalteredApp w(dependency::s_character_manager, dependency::derived_values);
  w.show();
  return a.exec();
}
