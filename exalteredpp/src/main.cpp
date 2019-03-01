#include "exalteredapp.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ExalteredApp w;
    w.show();

    return a.exec();
}
