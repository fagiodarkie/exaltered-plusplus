#include "exalteredapp.h"

#include <QGridLayout>
#include <QMenuBar>
#include "caste_style.h"
#include "dice_roller/dice_roller.h"
#include <screen/qloadcharacterscreen.h>
#include <screen/qcharacterattributes.h>

using namespace qt::screen;

void ExalteredApp::load_character_screen()
{
  character_info_screen_widget = new qcharacterinfoscreen(current_character, character_manager, this);
  setCentralWidget(character_info_screen_widget);
}

void ExalteredApp::load_attributes_screen()
{
  character_attributes_widget = new qcharacterattributes(current_character, this);
  setCentralWidget(character_attributes_widget);
}

void ExalteredApp::load_abilities_screen()
{
  character_abilities_widget = new qcharacterabilities(current_character, this);
  setCentralWidget(character_abilities_widget);
}

void ExalteredApp::load_vd_screen()
{
  character_defenses_widget = new qdefense_values_screen(current_character, derived_values_calculator, this);
  setCentralWidget(character_defenses_widget);
  connect(character_defenses_widget, &qdefense_values_screen::attack_wizard_invoked, this, &ExalteredApp::load_attack_wizard);
}

void ExalteredApp::load_attack_wizard()
{
  attack_wizard = new qt::wizard::attack_resolution_wizard(current_character, derived_values_calculator);
  setCentralWidget(attack_wizard);
  connect(attack_wizard, &qt::wizard::attack_resolution_wizard::outcome, this, &ExalteredApp::load_vd_screen);
}

void ExalteredApp::load_defense_wizard()
{
  defense_wizard = new qt::wizard::defense_resolution_wizard(current_character, derived_values_calculator);
  setCentralWidget(defense_wizard);
  connect(defense_wizard, &qt::wizard::defense_resolution_wizard::outcome, this, &ExalteredApp::load_vd_screen);
}

void ExalteredApp::load_essence_screen()
{
  character_essence_widget = new qessence_values_screen(current_character, this);
  setCentralWidget(character_essence_widget);
}

void ExalteredApp::load_virtues_screen()
{
  character_virtues_widget = new qwillpower_virtues_screen(current_character, this);
  setCentralWidget(character_virtues_widget);
}

void ExalteredApp::load_experience_screen()
{
  character_experience_widget = new qexperience_screen(current_character, character_manager, this);
  setCentralWidget(character_experience_widget);
}

void ExalteredApp::load_main_screen(std::shared_ptr<character::character> character)
{
  current_character = character;
  qt::style::SET_CASTE(character->type());
  character_manager.save_character(character);
  load_menu();
  load_character_screen();
}

void ExalteredApp::load_creation_wizard_screen()
{
  character_creation_wizard = new qt::wizard::character_creation_wizard(character_manager, derived_values_calculator, this);
  connect(character_creation_wizard, &qt::wizard::character_creation_wizard::character_created, this, &ExalteredApp::load_main_screen);
  connect(character_creation_wizard, &qt::wizard::character_creation_wizard::back_issued, this, &ExalteredApp::init_load_character_screen);
  setCentralWidget(character_creation_wizard);
}

void ExalteredApp::init_load_character_screen()
{
  load_character_screen_widget = new qloadcharacterscreen(character_manager, this);
  setCentralWidget(load_character_screen_widget);

  connect(load_character_screen_widget, &qloadcharacterscreen::character_loaded, this, &ExalteredApp::load_main_screen);
  connect(load_character_screen_widget, &qloadcharacterscreen::character_create_issued, this, &ExalteredApp::load_creation_wizard_screen);
}
