#ifndef EXALTEREDAPP_H
#define EXALTEREDAPP_H

#include <QMainWindow>

class ExalteredApp : public QMainWindow
{
  Q_OBJECT

  public:
    ExalteredApp(QWidget *parent = nullptr);
    ~ExalteredApp();
};

#endif // EXALTEREDAPP_H
