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

CONFIG += c++11

INCLUDEPATH += ../../headers \
    ../../headers/model \
    ../../headers/model/character \
    ../../headers/serialisation \
    ../../headers/qt \
    ../../headers/errors

SOURCES += \
    ../../src/model/character/character.cpp \
    ../../src/model/character/attributes/attribute.cpp \
    ../../src/model/character/attributes/attributes.cpp \
    ../../src/model/character/exalt/exalt_caste_abilities.cpp \
    ../../src/model/managers/character_manager.cpp \
    ../../src/serialisation/json_constants.cpp \
    ../../src/serialisation/filesystem_db.cpp \
    ../../src/qt/exalteredapp.cpp \
    ../../src/qt/main.cpp \
    ../../src/qt/screen/qloadcharacterscreen.cpp \
    ../../src/qt/screen/qmainscreen.cpp \
    ../../src/qt/layout/qborderlayout.cpp \
    ../../src/qt/widget/changeable_value_label.cpp \
    ../../src/qt/navigation/exalteredapp_navigation_logic.cpp \
    ../../src/errors/characternotfoundexception.cpp \
    ../../src/qt/screen/qcharacterinfoscreen.cpp \
    ../../src/qt/screen/qcharacterattributes.cpp \
    ../../src/qt/widget/name_value_widget.cpp \
    ../../src/model/character/abilities/ability.cpp \
    ../../src/model/character/abilities/abilities.cpp \
    ../../src/qt/screen/qcharacterabilities.cpp \
    ../../src/qt/navigation/exalteredapp_load_screen_logic.cpp \
    ../../src/model/character/abilities/ability_group.cpp \
    ../../src/model/character/abilities/specialisation.cpp \
    ../../src/errors/ability_not_found_exception.cpp \
    ../../src/errors/invalid_parameter.cpp \
    ../../src/model/character/abilities/default_ability_factory.cpp \
    ../../src/model/character/creation/character_type_model.cpp \
    ../../src/model/character/creation/character_creation_configuration.cpp \
    ../../src/qt/wizard/character_creation_wizard.cpp \
    ../../src/qt/wizard/character_creation_name_type_page.cpp \
    ../../src/qt/wizard/attributes_priority_page.cpp \
    ../../src/qt/wizard/character_creation_attribute_points_page.cpp \
    ../../src/qt/wizard/character_creation_favorite_abilities.cpp \
    ../../src/model/character/exalt/exalt_caste.cpp \
    ../../src/model/character/virtues/virtue.cpp \
    ../../src/model/character/power/willpower.cpp \
    ../../src/model/character/virtues/virtues.cpp

HEADERS += \
    ../../headers/model/character/attributes/attribute_names.h \
    ../../headers/model/character/character.h \
    ../../headers/model/character/attributes/attribute.h \
    ../../headers/model/character/attributes/attributes.h \
    ../../headers/model/managers/character_manager.h \
    ../../headers/model/text/character_text_constants.h \
    ../../headers/serialisation/serialisable.h \
    ../../headers/serialisation/json_constants.h \
    ../../headers/serialisation/db_abstraction.h \
    ../../headers/serialisation/filesystem_db.h \
    ../../headers/qt/exalteredapp.h \
    ../../headers/qt/screen/qloadcharacterscreen.h \
    ../../headers/qt/layout/qborderlayout.h \
    ../../headers/qt/label/interfacelabels.h \
    ../../headers/qt/screen/qmainscreen.h \
    ../../headers/qt/widget/changeable_value_label.h \
    ../../headers/errors/characternotfoundexception.h \
    ../../headers/errors/error_codes.h \
    ../../headers/qt/objects_factory.h \
    ../../headers/qt/screen/qcharacterinfoscreen.h \
    ../../headers/model/behavioral/name_value_pair.h \
    ../../headers/qt/widget/name_value_widget.h \
    ../../headers/qt/screen/qcharacterattributes.h \
    ../../headers/model/character/abilities/ability.h \
    ../../headers/model/character/abilities/ability_names.h \
    ../../headers/model/character/abilities/abilities.h \
    ../../headers/qt/screen/qcharacterabilities.h \
    ../../headers/model/character/abilities/ability_group.h \
    ../../headers/model/character/abilities/specialisation.h \
    ../../headers/errors/ability_not_found_exception.h \
    ../../headers/errors/invalid_parameter.h \
    ../../headers/model/character/abilities/abstract_ability_factory.h \
    ../../headers/model/character/abilities/default_ability_factory.h \
    ../../headers/model/character/creation/character_type_model.h \
    ../../headers/model/character/creation/character_creation_configuration.h \
    ../../headers/qt/wizard/character_creation_wizard.h \
    ../../headers/qt/wizard/character_creation_name_type_page.h \
    ../../headers/qt/wizard/attributes_priority_page.h \
    ../../headers/qt/wizard/character_creation_attribute_points_page.h \
    ../../headers/qt/wizard/character_creation_favorite_abilities.h \
    ../../headers/model/character/exalt/exalt_caste.h \
    ../../headers/model/character/virtues/virtues.h \
    ../../headers/model/character/virtues/virtue.h \
    ../../headers/model/character/virtues/virtue_names.h \
    ../../headers/model/character/power/willpower.h \
    ../../headers/common/reverse_search.h

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
