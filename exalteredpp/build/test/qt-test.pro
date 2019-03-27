QT -= gui

CONFIG += c++11 console
CONFIG -= app_bundle

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS
QMAKE_CXXFLAGS += --coverage -O0
QMAKE_LFLAGS += --coverage
# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += ../../headers \
    ../../headers/model \
    ../../headers/model/character \
    ../../headers/serialisation \
    ../../headers/qt \
    ../../headers/errors


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    ../../thirdparty/catch/catch.hpp \
    ../../headers/model/character/attributes/attribute.h \
    ../../headers/model/character/attributes/attributes.h \
    ../../headers/model/character/character.h \
    ../../headers/model/character/attributes/attribute_names.h \
    ../../headers/serialisation/json_constants.h \
    ../../headers/serialisation/db_abstraction.h \
    ../../headers/serialisation/filesystem_db.h \
    ../../headers/serialisation/serialisable.h \
    ../../headers/errors/characternotfoundexception.h \
    ../../headers/errors/error_codes.h \
    ../../headers/model/text/character_text_constants.h \
    ../../headers/model/managers/character_manager.h \
    ../../headers/errors/characternotfoundexception.h \
    ../../headers/errors/error_codes.h \
    ../../headers/model/behavioral/name_value_pair.h \
    ../../headers/model/character/abilities/abilities.h \
    ../../headers/model/character/abilities/ability.h \
    ../../headers/model/character/abilities/ability_names.h \
    ../../headers/model/character/attributes/attribute.h \
    ../../headers/model/character/attributes/attribute_names.h \
    ../../headers/model/character/attributes/attributes.h \
    ../../headers/model/character/character.h \
    ../../headers/model/managers/character_manager.h \
    ../../headers/model/text/character_text_constants.h \
    ../../headers/serialisation/db_abstraction.h \
    ../../headers/serialisation/filesystem_db.h \
    ../../headers/serialisation/json_constants.h \
    ../../headers/serialisation/serialisable.h

SOURCES += \
    ../../src/qt-test/main.cpp \
    ../../src/model/character/attributes/attribute.cpp \
    ../../src/model/character/attributes/attributes.cpp \
    ../../src/model/character/character.cpp \
    ../../src/test-case/attribute-test.cpp \
    ../../src/test-case/character-test.cpp \
    ../../src/test-case/attributes-test.cpp \
    ../../src/test-case/filesystem_db-test.cpp \
    ../../src/serialisation/filesystem_db.cpp \
    ../../src/serialisation/json_constants.cpp \
    ../../src/errors/characternotfoundexception.cpp \
    ../../src/test-case/exceptions-test.cpp \
    ../../src/test-case/character_manager-test.cpp \
    ../../src/model/managers/character_manager.cpp \
    ../../src/errors/characternotfoundexception.cpp \
    ../../src/model/character/abilities/abilities.cpp \
    ../../src/model/character/abilities/ability.cpp \
    ../../src/model/character/attributes/attribute.cpp \
    ../../src/model/character/attributes/attributes.cpp \
    ../../src/model/character/character.cpp \
    ../../src/model/managers/character_manager.cpp \
    ../../src/qt-test/main.cpp \
    ../../src/serialisation/filesystem_db.cpp \
    ../../src/serialisation/json_constants.cpp \
    ../../src/test-case/attribute-test.cpp \
    ../../src/test-case/attributes-test.cpp \
    ../../src/test-case/character-test.cpp \
    ../../src/test-case/character_manager-test.cpp \
    ../../src/test-case/exceptions-test.cpp \
    ../../src/test-case/filesystem_db-test.cpp \
    ../../src/test-case/ability-test.cpp \
    ../../src/test-case/abilities-test.cpp

