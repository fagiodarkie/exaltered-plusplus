#-------------------------------------------------
#
# Project created by QtCreator 2019-03-01T15:12:02
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = exalteredpp
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++14

INCLUDEPATH += ../../headers \
    ../../headers/serialisation \
    ../../headers/qt \
    ../../../core/core/headers \
    ../../../core/core/headers/calculator \
    ../../../core/core/headers/combat \
    ../../../core/core/headers/errors \
    ../../../core/core/headers/model \
    ../../../core/core/headers/model/character \
    ../../../core/core/headers/serialisation

LIBS += ../../../core/core/libdivinegames-core.a

SOURCES += \
    ../../src/qt/caste_style.cpp \
    ../../src/qt/dependencies.cpp \
    ../../src/qt/exalteredapp.cpp \
    ../../src/qt/layout/qborderlayout.cpp \
    ../../src/qt/main.cpp \
    ../../src/qt/navigation/exalteredapp_load_screen_logic.cpp \
    ../../src/qt/navigation/exalteredapp_navigation_logic.cpp \
    ../../src/qt/screen/qcharacterabilities.cpp \
    ../../src/qt/screen/qcharacterattributes.cpp \
    ../../src/qt/screen/qcharacterinfoscreen.cpp \
    ../../src/qt/screen/qcraftingscreen.cpp \
    ../../src/qt/screen/qdefense_values_screen.cpp \
    ../../src/qt/screen/qessence_values_screen.cpp \
    ../../src/qt/screen/qexperience_screen.cpp \
    ../../src/qt/screen/qhealth_screen.cpp \
    ../../src/qt/screen/qloadcharacterscreen.cpp \
    ../../src/qt/screen/qwillpower_virtues_screen.cpp \
    ../../src/qt/widget/ability_declination_selector.cpp \
    ../../src/qt/widget/add_ability_declination_dialog.cpp \
    ../../src/qt/widget/changeable_value_label.cpp \
    ../../src/qt/widget/experience_purchase_widget.cpp \
    ../../src/qt/widget/name_value_widget.cpp \
    ../../src/qt/widget/session_experience_logger.cpp \
    ../../src/qt/widget/with_next_continue_buttons.cpp \
    ../../src/qt/widget/with_progress_bar.cpp \
    ../../src/qt/wizard/chargen/ability_value_row.cpp \
    ../../src/qt/wizard/chargen/attributes_priority_page.cpp \
    ../../src/qt/wizard/chargen/character_creation_ability_values.cpp \
    ../../src/qt/wizard/chargen/character_creation_attribute_points_page.cpp \
    ../../src/qt/wizard/chargen/character_creation_name_type_page.cpp \
    ../../src/qt/wizard/chargen/character_creation_persona.cpp \
    ../../src/qt/wizard/chargen/character_creation_virtues_vice.cpp \
    ../../src/qt/wizard/chargen/character_creation_wizard.cpp \
    ../../src/qt/wizard/crafting/new_weapon_project.cpp \
    ../../src/qt/wizard/crafting/weapon_project_stat_widget.cpp \
    ../../src/qt/wizard/phys_defense/attack_parameters_page.cpp \
    ../../src/qt/wizard/phys_defense/defense_declaration_page.cpp \
    ../../src/qt/wizard/phys_defense/defense_resolution_wizard.cpp \
    ../../src/qt/wizard/phys_defense/final_damage_input_page.cpp \
    ../../src/serialisation/filesystem_db.cpp \
    ../../thirdparty/darkstyle/DarkStyle.cpp \
    ../../src/qt/wizard/phys_attack/attack_resolution_wizard.cpp \
    ../../src/qt/wizard/phys_attack/attack_declaration_precision_page.cpp \
    ../../src/qt/wizard/phys_attack/provide_defense_value_page.cpp \
    ../../src/qt/wizard/phys_attack/final_damage_results_push_knock_page.cpp \
    ../../src/qt/wizard/phys_attack/provide_balance_details_page.cpp \
    ../../src/qt/wizard/phys_attack/attack_result_page.cpp


HEADERS += \
    ../../headers/qt/caste_style.h \
    ../../headers/qt/dependencies.h \
    ../../headers/qt/exalteredapp.h \
    ../../headers/qt/label/interfacelabels.h \
    ../../headers/qt/layout/layout_constants.h \
    ../../headers/qt/layout/layout_helper_factories.h \
    ../../headers/qt/layout/qborderlayout.h \
    ../../headers/qt/screen/qcharacterabilities.h \
    ../../headers/qt/screen/qcharacterattributes.h \
    ../../headers/qt/screen/qcharacterinfoscreen.h \
    ../../headers/qt/screen/qcraftingscreen.h \
    ../../headers/qt/screen/qdefense_values_screen.h \
    ../../headers/qt/screen/qessence_values_screen.h \
    ../../headers/qt/screen/qexperience_screen.h \
    ../../headers/qt/screen/qhealth_screen.h \
    ../../headers/qt/screen/qloadcharacterscreen.h \
    ../../headers/qt/screen/qwillpower_virtues_screen.h \
    ../../headers/qt/widget/ability_declination_selector.h \
    ../../headers/qt/widget/add_ability_declination_dialog.h \
    ../../headers/qt/widget/changeable_value_label.h \
    ../../headers/qt/widget/experience_purchase_widget.h \
    ../../headers/qt/widget/name_value_widget.h \
    ../../headers/qt/widget/session_experience_logger.h \
    ../../headers/qt/widget/std_compatible.h \
    ../../headers/qt/widget/with_next_continue_buttons.h \
    ../../headers/qt/widget/with_progress_bar.h \
    ../../headers/qt/wizard/chargen/ability_value_row.h \
    ../../headers/qt/wizard/chargen/attributes_priority_page.h \
    ../../headers/qt/wizard/chargen/character_creation_ability_values.h \
    ../../headers/qt/wizard/chargen/character_creation_attribute_points_page.h \
    ../../headers/qt/wizard/chargen/character_creation_name_type_page.h \
    ../../headers/qt/wizard/chargen/character_creation_persona.h \
    ../../headers/qt/wizard/chargen/character_creation_virtues_vice.h \
    ../../headers/qt/wizard/chargen/character_creation_wizard.h \
    ../../headers/qt/wizard/crafting/new_weapon_project.h \
    ../../headers/qt/wizard/crafting/weapon_project_stat_widget.h \
    ../../headers/qt/wizard/phys_defense/attack_parameters_page.h \
    ../../headers/qt/wizard/phys_defense/defense_declaration_page.h \
    ../../headers/qt/wizard/phys_defense/defense_resolution_wizard.h \
    ../../headers/qt/wizard/phys_defense/final_damage_input_page.h \
    ../../headers/serialisation/filesystem_db.h \
    ../../thirdparty/darkstyle/DarkStyle.h \
    ../../headers/qt/wizard/phys_attack/attack_resolution_wizard.h \
    ../../headers/qt/wizard/phys_attack/attack_declaration_precision_page.h \
    ../../headers/qt/wizard/phys_attack/provide_defense_value_page.h \
    ../../headers/qt/wizard/phys_attack/final_damage_results_push_knock_page.h \
    ../../headers/qt/wizard/phys_attack/provide_balance_details_page.h \
    ../../headers/qt/wizard/phys_attack/attack_result_page.h

CONFIG += mobility
MOBILITY = 

debug {
    QMAKE_CXXFLAGS += --coverage -O0
    QMAKE_LFLAGS += --coverage
}

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
