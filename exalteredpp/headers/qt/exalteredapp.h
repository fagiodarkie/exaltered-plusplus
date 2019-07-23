#pragma once

#include <QStackedLayout>
#include <QMainWindow>

#include "screen/qloadcharacterscreen.h"
#include "screen/qcharacterinfoscreen.h"
#include "screen/qcharacterattributes.h"
#include "screen/qcharacterabilities.h"
#include "wizard/character_creation_wizard.h"
#include "screen/qmainscreen.h"

using namespace qt::screen;

class ExalteredApp : public QMainWindow
{
  Q_OBJECT

  public:
    ExalteredApp(manager::character_manager& c_manager);
    ~ExalteredApp();

  public slots:
    void        load_main_screen(std::shared_ptr<character::character> character);
    void        load_character_screen();
    void        load_attributes_screen();
    void        load_abilities_screen();
    void        load_creation_wizard_screen();

  protected:
    void        init_load_character_screen();
    void        load_menu();

  private:
    QLayout*    create_layout_for_widget(QWidget* content) const;
    void        clear_layout(QWidget* current_layout);

    // screens
    qloadcharacterscreen*                       load_character_screen_widget;
    qmainscreen*                                main_screen_widget;
    qcharacterinfoscreen*                       character_info_screen_widget;
    qcharacterattributes*                       character_attributes_widget;
    qcharacterabilities*                        character_abilities_widget;
    qt::wizard::character_creation_wizard*      character_creation_wizard;

    manager::character_manager&  character_manager;
    std::shared_ptr<character::character>        current_character;
};
