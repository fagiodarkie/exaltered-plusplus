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
    ../../src/calculator/cost_worker/vice_cost_worker.cpp \
    ../../src/model/character/narrative/ability_purchase.cpp \
    ../../src/model/character/narrative/attribute_purchase.cpp \
    ../../src/model/character/narrative/background_purchase.cpp \
    ../../src/model/character/narrative/charm_purchase.cpp \
    ../../src/model/character/narrative/essence_purchase.cpp \
    ../../src/model/character/narrative/experience_award.cpp \
    ../../src/model/character/narrative/experience_cluster.cpp \
    ../../src/model/character/narrative/session_awards.cpp \
    ../../src/model/character/narrative/specialisation_purchase.cpp \
    ../../src/model/character/narrative/vice_purchase.cpp \
    ../../src/model/character/narrative/virtue_purchase.cpp \
    ../../src/model/character/narrative/willpower_purchase.cpp \
    ../../src/qt/screen/qexperience_screen.cpp \
    ../../src/qt/widget/experience_purchase_widget.cpp \
    ../../src/qt/widget/session_experience_logger.cpp \
    ../../src/calculator/derived_value_calculator.cpp \
    ../../src/calculator/worker/exalt_worker.cpp \
    ../../src/errors/ability_not_found_exception.cpp \
    ../../src/errors/characternotfoundexception.cpp \
    ../../src/errors/invalid_parameter.cpp \
    ../../src/model/character/abilities/abilities.cpp \
    ../../src/model/character/abilities/ability.cpp \
    ../../src/model/character/abilities/ability_group.cpp \
    ../../src/model/character/abilities/specialisation.cpp \
    ../../src/model/character/attributes/attribute.cpp \
    ../../src/model/character/attributes/attributes.cpp \
    ../../src/model/character/character.cpp \
    ../../src/model/character/creation/character_creation_configuration.cpp \
    ../../src/model/character/creation/character_type_model.cpp \
    ../../src/model/character/exalt/exalt_caste.cpp \
    ../../src/model/character/exalt/exalt_caste_abilities.cpp \
    ../../src/model/character/narrative/backgrounds.cpp \
    ../../src/model/character/power/essence.cpp \
    ../../src/model/character/power/health.cpp \
    ../../src/model/character/power/logos.cpp \
    ../../src/model/character/power/power_container.cpp \
    ../../src/model/character/power/willpower.cpp \
    ../../src/model/character/social/persona.cpp \
    ../../src/model/character/social/philosophy.cpp \
    ../../src/model/character/virtues/virtue.cpp \
    ../../src/model/character/virtues/virtues.cpp \
    ../../src/model/managers/character_manager.cpp \
    ../../src/qt/exalteredapp.cpp \
    ../../src/qt/layout/qborderlayout.cpp \
    ../../src/qt/main.cpp \
    ../../src/qt/navigation/exalteredapp_load_screen_logic.cpp \
    ../../src/qt/navigation/exalteredapp_navigation_logic.cpp \
    ../../src/qt/screen/qcharacterabilities.cpp \
    ../../src/qt/screen/qcharacterattributes.cpp \
    ../../src/qt/screen/qcharacterinfoscreen.cpp \
    ../../src/qt/screen/qloadcharacterscreen.cpp \
    ../../src/qt/screen/qwillpower_virtues_screen.cpp \
    ../../src/qt/widget/ability_declination_selector.cpp \
    ../../src/qt/widget/changeable_value_label.cpp \
    ../../src/qt/widget/name_value_widget.cpp \
    ../../src/qt/wizard/ability_value_row.cpp \
    ../../src/qt/wizard/attributes_priority_page.cpp \
    ../../src/qt/wizard/character_creation_ability_values.cpp \
    ../../src/qt/wizard/character_creation_attribute_points_page.cpp \
    ../../src/qt/wizard/character_creation_name_type_page.cpp \
    ../../src/qt/wizard/character_creation_persona.cpp \
    ../../src/qt/wizard/character_creation_wizard.cpp \
    ../../src/serialisation/filesystem_db.cpp \
    ../../src/serialisation/json_constants.cpp \
    ../../src/qt/wizard/character_creation_virtues_vice.cpp \
    ../../src/qt/screen/qdefense_values_screen.cpp \
    ../../src/qt/screen/qessence_values_screen.cpp \
    ../../src/qt/widget/with_progress_bar.cpp \
    ../../src/qt/widget/add_ability_declination_dialog.cpp \
    ../../src/model/character/narrative/experience.cpp \
    ../../src/calculator/experience_purchase_cost_calculator.cpp \
    ../../src/calculator/cost_worker/attribute_cost_worker.cpp \
    ../../src/calculator/cost_worker/specialisation_cost_worker.cpp \
    ../../src/calculator/cost_worker/virtue_cost_worker.cpp \
    ../../src/calculator/cost_worker/essence_cost_worker.cpp \
    ../../src/calculator/cost_worker/willpower_cost_worker.cpp \
    ../../src/calculator/cost_worker/ability_cost_worker.cpp \
    ../../thirdparty/darkstyle/DarkStyle.cpp

HEADERS += \
    ../../headers/calculator/cost_worker/vice_cost_worker.h \
    ../../headers/calculator/derived_value_calculator.h \
    ../../headers/calculator/derived_value_definitions.h \
    ../../headers/calculator/worker/abstract_calculator_worker.h \
    ../../headers/calculator/worker/common_worker.h \
    ../../headers/calculator/worker/exalt_worker.h \
    ../../headers/calculator/worker/rounding_type.h \
    ../../headers/common/reverse_search.h \
    ../../headers/errors/ability_not_found_exception.h \
    ../../headers/errors/characternotfoundexception.h \
    ../../headers/errors/error_codes.h \
    ../../headers/errors/invalid_parameter.h \
    ../../headers/model/behavioral/name_value_pair.h \
    ../../headers/model/character/abilities/abilities.h \
    ../../headers/model/character/abilities/ability.h \
    ../../headers/model/character/abilities/ability_group.h \
    ../../headers/model/character/abilities/ability_names.h \
    ../../headers/model/character/abilities/specialisation.h \
    ../../headers/model/character/attributes/attribute.h \
    ../../headers/model/character/attributes/attribute_names.h \
    ../../headers/model/character/attributes/attributes.h \
    ../../headers/model/character/character.h \
    ../../headers/model/character/creation/character_creation_configuration.h \
    ../../headers/model/character/creation/character_type_model.h \
    ../../headers/model/character/exalt/exalt_caste.h \
    ../../headers/model/character/narrative/abstract_purchase.h \
    ../../headers/model/character/narrative/attribute_purchase.h \
    ../../headers/model/character/narrative/background_purchase.h \
    ../../headers/model/character/narrative/backgrounds.h \
    ../../headers/model/character/narrative/charm_purchase.h \
    ../../headers/model/character/narrative/ability_purchase.h \
    ../../headers/model/character/narrative/essence_purchase.h \
    ../../headers/model/character/narrative/experience_award.h \
    ../../headers/model/character/narrative/experience_cluster.h \
    ../../headers/model/character/narrative/experience_defines.h \
    ../../headers/model/character/narrative/session_awards.h \
    ../../headers/model/character/narrative/specialisation_purchase.h \
    ../../headers/model/character/narrative/vice_purchase.h \
    ../../headers/model/character/narrative/virtue_purchase.h \
    ../../headers/model/character/narrative/willpower_purchase.h \
    ../../headers/model/character/power/essence.h \
    ../../headers/model/character/power/health.h \
    ../../headers/model/character/power/logos.h \
    ../../headers/model/character/power/power_container.h \
    ../../headers/model/character/power/willpower.h \
    ../../headers/model/character/social/emotions_names.h \
    ../../headers/model/character/social/persona.h \
    ../../headers/model/character/social/philosophy.h \
    ../../headers/model/character/social/social_specifics.h \
    ../../headers/model/character/virtues/virtue.h \
    ../../headers/model/character/virtues/virtue_names.h \
    ../../headers/model/character/virtues/virtues.h \
    ../../headers/model/managers/character_manager.h \
    ../../headers/model/text/character_text_constants.h \
    ../../headers/qt/exalteredapp.h \
    ../../headers/qt/label/interfacelabels.h \
    ../../headers/qt/layout/layout_constants.h \
    ../../headers/qt/layout/qborderlayout.h \
    ../../headers/qt/screen/qcharacterabilities.h \
    ../../headers/qt/screen/qcharacterattributes.h \
    ../../headers/qt/screen/qcharacterinfoscreen.h \
    ../../headers/qt/screen/qexperience_screen.h \
    ../../headers/qt/screen/qloadcharacterscreen.h \
    ../../headers/qt/screen/qwillpower_virtues_screen.h \
    ../../headers/qt/widget/ability_declination_selector.h \
    ../../headers/qt/widget/changeable_value_label.h \
    ../../headers/qt/widget/experience_purchase_widget.h \
    ../../headers/qt/widget/name_value_widget.h \
    ../../headers/qt/widget/session_experience_logger.h \
    ../../headers/qt/widget/with_progress_bar.h \
    ../../headers/qt/wizard/ability_value_row.h \
    ../../headers/qt/wizard/attributes_priority_page.h \
    ../../headers/qt/wizard/character_creation_ability_values.h \
    ../../headers/qt/wizard/character_creation_attribute_points_page.h \
    ../../headers/qt/wizard/character_creation_name_type_page.h \
    ../../headers/qt/wizard/character_creation_persona.h \
    ../../headers/qt/wizard/character_creation_wizard.h \
    ../../headers/serialisation/db_abstraction.h \
    ../../headers/serialisation/filesystem_db.h \
    ../../headers/serialisation/json_constants.h \
    ../../headers/qt/wizard/character_creation_virtues_vice.h \
    ../../headers/qt/widget/std_compatible.h \
    ../../thirdparty/darkstyle/DarkStyle.h \
    ../../thirdparty/serialisable/serialisable.hpp \
    ../../headers/qt/dependencies.h \
    ../../headers/qt/screen/qdefense_values_screen.h \
    ../../headers/qt/screen/qessence_values_screen.h \
    ../../headers/qt/widget/add_ability_declination_dialog.h \
    ../../headers/model/character/narrative/experience.h \
    ../../headers/qt/caste_style.h \
    ../../headers/calculator/experience_purchase_cost_calculator.h \
    ../../headers/calculator/cost_worker/abstract_cost_worker.h \
    ../../headers/calculator/cost_worker/attribute_cost_worker.h \
    ../../headers/calculator/cost_worker/specialisation_cost_worker.h \
    ../../headers/calculator/cost_worker/ability_cost_worker.h \
    ../../headers/calculator/cost_worker/virtue_cost_worker.h \
    ../../headers/calculator/cost_worker/essence_cost_worker.h \
    ../../headers/calculator/cost_worker/willpower_cost_worker.h

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
