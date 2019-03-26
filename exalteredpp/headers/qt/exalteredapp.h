#pragma once

#include <QStackedLayout>
#include <QWidget>

#include "screen/qloadcharacterscreen.h"
#include "screen/qmainscreen.h"

using namespace qt::screen;

class ExalteredApp : public QWidget
{
  Q_OBJECT

  public:
    ExalteredApp(QWidget *parent = nullptr);
    ~ExalteredApp();

  public slots:
    void load_character_screen(QSharedPointer<character::character> character);

  protected:
    void init_load_character_screen();

  private:
    QLayout* create_layout_for_widget(QWidget* content) const;
    void clear_layout(QWidget* current_layout);

    // screens
    qloadcharacterscreen* load_character_screen_widget;
    qmainscreen* character_screen_widget;
    QStackedLayout* stacked_layout;
};
