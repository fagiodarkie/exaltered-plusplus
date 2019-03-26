#include "qt/exalteredapp.h"
#include "objects_factory.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ExalteredApp w(qt::model_factory::s_character_manager);
    w.show();
    return a.exec();
}
