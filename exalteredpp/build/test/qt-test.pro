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
    ../../headers/qt


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    ../../headers/model/character/attributes/attribute.h \
    ../../headers/model/character/attributes/attributeNames.h \
    ../../headers/model/character/attributes/attributes.h \
    ../../headers/model/character/character.h \
    ../../headers/serialisation/json_constants.h \
    ../../headers/serialisation/serialisable.h \
    ../../thirdparty/catch/catch.hpp

SOURCES += \
    ../../src/model/character/attributes/attribute.cpp \
    ../../src/model/character/attributes/attributes.cpp \
    ../../src/model/character/character.cpp \
    ../../src/qt-test/main.cpp \
    ../../src/test-case/attribute-test.cpp \
    ../../src/test-case/character-test.cpp \
    ../../src/serialisation/json_constants.cpp

