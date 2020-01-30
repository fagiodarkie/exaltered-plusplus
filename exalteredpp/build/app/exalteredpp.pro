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

CONFIG += c++17

INCLUDEPATH += ../../headers \
    ../../headers/model \
    ../../headers/model/character \
    ../../headers/serialisation \
    ../../headers/qt \
    ../../headers/errors \
    ../../headers/calculator

SOURCES += \
    ../../src/calculator/dice_roller/dice_roller_options.cpp \
    ../../src/combat/physical_attack.cpp \
    ../../src/calculator/cost_worker/ability_cost_worker.cpp \
    ../../src/calculator/cost_worker/attribute_cost_worker.cpp \
    ../../src/calculator/cost_worker/essence_cost_worker.cpp \
    ../../src/calculator/cost_worker/specialisation_cost_worker.cpp \
    ../../src/calculator/cost_worker/vice_cost_worker.cpp \
    ../../src/calculator/cost_worker/virtue_cost_worker.cpp \
    ../../src/calculator/cost_worker/willpower_cost_worker.cpp \
    ../../src/calculator/derived_value_calculator.cpp \
    ../../src/calculator/experience_purchase_cost_calculator.cpp \
    ../../src/calculator/worker/exalt_worker.cpp \
    ../../src/combat/weapon.cpp \
    ../../src/errors/ability_not_found_exception.cpp \
    ../../src/errors/characternotfoundexception.cpp \
    ../../src/errors/invalid_parameter.cpp \
    ../../src/model/abilities/abilities.cpp \
    ../../src/model/abilities/ability.cpp \
    ../../src/model/abilities/specialisation.cpp \
    ../../src/model/attributes/attributes.cpp \
    ../../src/model/character/character.cpp \
    ../../src/model/character/creation/character_creation_configuration.cpp \
    ../../src/model/character/creation/character_type_model.cpp \
    ../../src/model/character/exalt/exalt_caste.cpp \
    ../../src/model/character/exalt/exalt_caste_abilities.cpp \
    ../../src/model/managers/character_manager.cpp \
    ../../src/model/narrative/ability_purchase.cpp \
    ../../src/model/narrative/attribute_purchase.cpp \
    ../../src/model/narrative/background_purchase.cpp \
    ../../src/model/narrative/backgrounds.cpp \
    ../../src/model/narrative/charm_purchase.cpp \
    ../../src/model/narrative/essence_purchase.cpp \
    ../../src/model/narrative/experience.cpp \
    ../../src/model/narrative/experience_award.cpp \
    ../../src/model/narrative/experience_cluster.cpp \
    ../../src/model/narrative/session_awards.cpp \
    ../../src/model/narrative/specialisation_purchase.cpp \
    ../../src/model/narrative/vice_purchase.cpp \
    ../../src/model/narrative/virtue_purchase.cpp \
    ../../src/model/narrative/willpower_purchase.cpp \
    ../../src/model/power/essence.cpp \
    ../../src/model/power/health.cpp \
    ../../src/model/power/logos.cpp \
    ../../src/model/power/willpower.cpp \
    ../../src/model/social/persona.cpp \
    ../../src/model/social/philosophy.cpp \
    ../../src/model/virtues/virtue.cpp \
    ../../src/model/virtues/virtues.cpp \
    ../../src/qt/caste_style.cpp \
    ../../src/qt/exalteredapp.cpp \
    ../../src/qt/layout/qborderlayout.cpp \
    ../../src/qt/main.cpp \
    ../../src/qt/navigation/exalteredapp_load_screen_logic.cpp \
    ../../src/qt/navigation/exalteredapp_navigation_logic.cpp \
    ../../src/qt/screen/qcharacterabilities.cpp \
    ../../src/qt/screen/qcharacterattributes.cpp \
    ../../src/qt/screen/qcharacterinfoscreen.cpp \
    ../../src/qt/screen/qdefense_values_screen.cpp \
    ../../src/qt/screen/qessence_values_screen.cpp \
    ../../src/qt/screen/qexperience_screen.cpp \
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
    ../../src/qt/wizard/ability_value_row.cpp \
    ../../src/qt/wizard/attributes_priority_page.cpp \
    ../../src/qt/wizard/character_creation_ability_values.cpp \
    ../../src/qt/wizard/character_creation_attribute_points_page.cpp \
    ../../src/qt/wizard/character_creation_name_type_page.cpp \
    ../../src/qt/wizard/character_creation_persona.cpp \
    ../../src/qt/wizard/character_creation_virtues_vice.cpp \
    ../../src/qt/wizard/character_creation_wizard.cpp \
    ../../src/serialisation/filesystem_db.cpp \
    ../../src/serialisation/json_constants.cpp \
    ../../thirdparty/darkstyle/DarkStyle.cpp \
    ../../src/qt/wizard/attack_resolution_wizard.cpp \
    ../../src/qt/wizard/attack_declaration_precision_page.cpp \
    ../../src/qt/wizard/provide_defense_value_page.cpp \
    ../../src/qt/wizard/final_damage_results_push_knock_page.cpp \
    ../../src/qt/wizard/provide_balance_details_page.cpp \
    ../../src/qt/wizard/attack_result_page.cpp

HEADERS += \
    ../../headers/calculator/abstract_dice_thrower.h \
    ../../headers/combat/attack_defines.h \
    ../../headers/combat/physical_attack.h \
    ../../headers/calculator/cost_worker/ability_cost_worker.h \
    ../../headers/calculator/cost_worker/abstract_cost_worker.h \
    ../../headers/calculator/cost_worker/attribute_cost_worker.h \
    ../../headers/calculator/cost_worker/essence_cost_worker.h \
    ../../headers/calculator/cost_worker/specialisation_cost_worker.h \
    ../../headers/calculator/cost_worker/vice_cost_worker.h \
    ../../headers/calculator/cost_worker/virtue_cost_worker.h \
    ../../headers/calculator/cost_worker/willpower_cost_worker.h \
    ../../headers/calculator/derived_value_calculator.h \
    ../../headers/calculator/derived_value_definitions.h \
    ../../headers/calculator/dice_roller/abstract_dice_roller.h \
    ../../headers/calculator/dice_roller/dice_roller.h \
    ../../headers/calculator/dice_roller/dice_roller_options.h \
    ../../headers/calculator/dice_thrower.h \
    ../../headers/calculator/dice_thrower/abstract_dice_roller.h \
    ../../headers/calculator/dice_thrower/dice_roller_options.h \
    ../../headers/calculator/experience_purchase_cost_calculator.h \
    ../../headers/calculator/worker/abstract_calculator_worker.h \
    ../../headers/calculator/worker/common_worker.h \
    ../../headers/calculator/worker/exalt_worker.h \
    ../../headers/calculator/worker/rounding_type.h \
    ../../headers/combat/action_defines.h \
    ../../headers/combat/attack_defines.h \
    ../../headers/combat/physical_attack.h \
    ../../headers/combat/weapon.h \
    ../../headers/common/reverse_search.h \
    ../../headers/errors/ability_not_found_exception.h \
    ../../headers/errors/characternotfoundexception.h \
    ../../headers/errors/error_codes.h \
    ../../headers/errors/invalid_parameter.h \
    ../../headers/model/abilities/ability_names.h \
    ../../headers/model/behavioral/name_value_pair.h \
    ../../headers/model/abilities/abilities.h \
    ../../headers/model/abilities/ability.h \
    ../../headers/model/abilities/ability.h \
    ../../headers/model/abilities/specialisation.h \
    ../../headers/model/attributes/attribute_names.h \
    ../../headers/model/attributes/attributes.h \
    ../../headers/model/character/character.h \
    ../../headers/model/character/creation/character_creation_configuration.h \
    ../../headers/model/character/creation/character_type_model.h \
    ../../headers/model/character/exalt/exalt_caste.h \
    ../../headers/model/narrative/ability_purchase.h \
    ../../headers/model/narrative/abstract_purchase.h \
    ../../headers/model/narrative/attribute_purchase.h \
    ../../headers/model/narrative/background_purchase.h \
    ../../headers/model/narrative/backgrounds.h \
    ../../headers/model/narrative/charm_purchase.h \
    ../../headers/model/narrative/essence_purchase.h \
    ../../headers/model/narrative/experience.h \
    ../../headers/model/narrative/experience_award.h \
    ../../headers/model/narrative/experience_cluster.h \
    ../../headers/model/narrative/experience_defines.h \
    ../../headers/model/narrative/session_awards.h \
    ../../headers/model/narrative/specialisation_purchase.h \
    ../../headers/model/narrative/vice_purchase.h \
    ../../headers/model/narrative/virtue_purchase.h \
    ../../headers/model/narrative/willpower_purchase.h \
    ../../headers/model/power/essence.h \
    ../../headers/model/power/health.h \
    ../../headers/model/power/logos.h \
    ../../headers/model/power/willpower.h \
    ../../headers/model/social/emotions_names.h \
    ../../headers/model/social/persona.h \
    ../../headers/model/social/philosophy.h \
    ../../headers/model/social/social_specifics.h \
    ../../headers/model/virtues/virtue.h \
    ../../headers/model/virtues/virtue_names.h \
    ../../headers/model/virtues/virtues.h \
    ../../headers/model/managers/character_manager.h \
    ../../headers/model/text/character_text_constants.h \
    ../../headers/qt/caste_style.h \
    ../../headers/qt/dependencies.h \
    ../../headers/qt/exalteredapp.h \
    ../../headers/qt/label/interfacelabels.h \
    ../../headers/qt/layout/layout_constants.h \
    ../../headers/qt/layout/qborderlayout.h \
    ../../headers/qt/screen/qcharacterabilities.h \
    ../../headers/qt/screen/qcharacterattributes.h \
    ../../headers/qt/screen/qcharacterinfoscreen.h \
    ../../headers/qt/screen/qdefense_values_screen.h \
    ../../headers/qt/screen/qessence_values_screen.h \
    ../../headers/qt/screen/qexperience_screen.h \
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
    ../../headers/qt/wizard/ability_value_row.h \
    ../../headers/qt/wizard/attributes_priority_page.h \
    ../../headers/qt/wizard/character_creation_ability_values.h \
    ../../headers/qt/wizard/character_creation_attribute_points_page.h \
    ../../headers/qt/wizard/character_creation_name_type_page.h \
    ../../headers/qt/wizard/character_creation_persona.h \
    ../../headers/qt/wizard/character_creation_virtues_vice.h \
    ../../headers/qt/wizard/character_creation_wizard.h \
    ../../headers/serialisation/db_abstraction.h \
    ../../headers/serialisation/filesystem_db.h \
    ../../headers/serialisation/json_constants.h \
    ../../thirdparty/darkstyle/DarkStyle.h \
    ../../thirdparty/serialisable/serialisable.hpp \
    ../../headers/qt/wizard/attack_resolution_wizard.h \
    ../../headers/qt/wizard/attack_declaration_precision_page.h \
    ../../headers/qt/wizard/provide_defense_value_page.h \
    ../../headers/qt/wizard/final_damage_results_push_knock_page.h \
    ../../headers/qt/wizard/provide_balance_details_page.h \
    ../../headers/qt/wizard/attack_result_page.h

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
