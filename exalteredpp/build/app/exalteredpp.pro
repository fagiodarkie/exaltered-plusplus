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
    ../../src/qt/screen/qcharacterinfoscreen.cpp

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
    ../../src/qt/screen/qcharacterinfoscreen \
    ../../headers/qt/screen/qcharacterinfoscreen.h

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
