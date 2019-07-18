#include "exalteredapp.h"

#include <QGridLayout>
#include <QMenuBar>
#include <screen/qmainscreen.h>
#include <screen/qloadcharacterscreen.h>
#include <screen/qcharacterattributes.h>

using namespace qt::screen;

void ExalteredApp::load_character_screen()
{
  character_info_screen_widget = new qcharacterinfoscreen(current_character.get(), character_manager.get(), this);
  setCentralWidget(character_info_screen_widget);
}

void ExalteredApp::load_attributes_screen()
{
  character_attributes_widget = new qcharacterattributes(current_character.get(), this);
  setCentralWidget(character_attributes_widget);
}

void ExalteredApp::load_abilities_screen()
{
  character_abilities_widget = new qcharacterabilities(current_character.get(), this);
  setCentralWidget(character_abilities_widget);
}

void ExalteredApp::load_main_screen(std::shared_ptr<character::character> character)
{
  current_character = character;
  character_manager->save_character(character);
  main_screen_widget = new qmainscreen(this);
  setCentralWidget(main_screen_widget);
  load_menu();
}

void ExalteredApp::load_creation_wizard_screen()
{
  character_creation_wizard = new qt::wizard::character_creation_wizard(character_manager.get(), this);
  connect(character_creation_wizard, &qt::wizard::character_creation_wizard::character_created, this, &ExalteredApp::load_main_screen);
  connect(character_creation_wizard, &qt::wizard::character_creation_wizard::back_issued, this, &ExalteredApp::init_load_character_screen);
  setCentralWidget(character_creation_wizard);
}

void ExalteredApp::init_load_character_screen()
{
  load_character_screen_widget = new qloadcharacterscreen(character_manager.get(), this);
  setCentralWidget(load_character_screen_widget);

  connect(load_character_screen_widget, &qloadcharacterscreen::character_loaded, this, &ExalteredApp::load_main_screen);
  connect(load_character_screen_widget, &qloadcharacterscreen::character_create_issued, this, &ExalteredApp::load_creation_wizard_screen);
}
