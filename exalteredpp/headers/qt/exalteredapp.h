#pragma once

#include <QStackedLayout>
#include <QMainWindow>

#include "screen/qloadcharacterscreen.h"
#include "screen/qcharacterinfoscreen.h"
#include "screen/qcharacterattributes.h"
#include "screen/qcharacterabilities.h"
#include "screen/qdefense_values_screen.h"
#include "screen/qessence_values_screen.h"
#include "screen/qwillpower_virtues_screen.h"
#include "screen/qexperience_screen.h"
#include "wizard/character_creation_wizard.h"
#include "screen/qmainscreen.h"

#include "derived_value_calculator.h"

using namespace qt::screen;

class ExalteredApp : public QMainWindow
{
  Q_OBJECT

  public:
    ExalteredApp(manager::character_manager& c_manager,
                 calculator::derived_value_calculator& derived_values_calculator);
    ~ExalteredApp();

  public slots:
    void        load_main_screen(std::shared_ptr<character::character> character);
    void        load_character_screen();
    void        load_attributes_screen();
    void        load_abilities_screen();
    void        load_creation_wizard_screen();
    void        load_vd_screen();
    void        load_essence_screen();
    void        load_virtues_screen();
    void        load_experience_screen();

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
    qdefense_values_screen*                     character_defenses_widget;
    qessence_values_screen*                     character_essence_widget;
    qwillpower_virtues_screen*                  character_virtues_widget;
    qexperience_screen*                         character_experience_widget;

    qt::wizard::character_creation_wizard*      character_creation_wizard;

    manager::character_manager&                 character_manager;
    calculator::derived_value_calculator&       derived_values_calculator;
    std::shared_ptr<character::character>       current_character;
};
