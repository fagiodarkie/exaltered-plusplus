#pragma once

#include <QWidget>
#include <QPointer>
#include "character.h"

namespace qt
{
  class main_screen_navigation_logic : public QWidget
  {
    Q_OBJECT

  public:
    main_screen_navigation_logic(QWidget *parent, QWidget* screen);

  public slots:
    void load_character_screen(QSharedPointer<character::character> character) const;

  protected:
    void init_load_character_screen();
    virtual ~main_screen_navigation_logic() = default;

  private:
    QPointer<QWidget> master_screen;
    QLayout* create_layout_for_widget(QWidget* content) const;
  };
}
