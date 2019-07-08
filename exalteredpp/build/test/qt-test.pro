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
    ../../headers/test-case \
    ../../headers/errors


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
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
    ../../headers/model/character/abilities/abstract_ability_factory.h \
    ../../headers/model/character/abilities/default_ability_factory.h \
    ../../headers/model/character/abilities/specialisation.h \
    ../../headers/model/character/attributes/attribute.h \
    ../../headers/model/character/attributes/attribute_names.h \
    ../../headers/model/character/attributes/attributes.h \
    ../../headers/model/character/character.h \
    ../../headers/model/character/creation/character_creation_configuration.h \
    ../../headers/model/character/creation/character_type_model.h \
    ../../headers/model/character/exalt/exalt_caste.h \
    ../../headers/model/character/narrative/backgrounds.h \
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
    ../../headers/serialisation/db_abstraction.h \
    ../../headers/serialisation/filesystem_db.h \
    ../../headers/serialisation/json_constants.h \
    ../../headers/serialisation/serialisable.h \
    ../../headers/test-case/ability_factory_mock.h \
    ../../headers/test-case/db_abstraction_mock.h \
    ../../headers/qt-test/quick_chargen.h

SOURCES += \
    ../../src/errors/ability_not_found_exception.cpp \
    ../../src/errors/characternotfoundexception.cpp \
    ../../src/errors/invalid_parameter.cpp \
    ../../src/model/character/abilities/abilities.cpp \
    ../../src/model/character/abilities/ability.cpp \
    ../../src/model/character/abilities/ability_group.cpp \
    ../../src/model/character/abilities/default_ability_factory.cpp \
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
    ../../src/qt-test/main.cpp \
    ../../src/qt-test/quick_chargen.cpp \
    ../../src/serialisation/filesystem_db.cpp \
    ../../src/serialisation/json_constants.cpp \
    ../../src/test-case/errors/exceptions-test.cpp \
    ../../src/test-case/managers/ability-factory-test.cpp \
    ../../src/test-case/managers/character_manager-test.cpp \
    ../../src/test-case/managers/filesystem_db-test.cpp \
    ../../src/test-case/model/abilities/abilities-test.cpp \
    ../../src/test-case/model/abilities/ability-group-test.cpp \
    ../../src/test-case/model/abilities/ability-test.cpp \
    ../../src/test-case/model/abilities/specialisation-test.cpp \
    ../../src/test-case/model/attributes/attribute-test.cpp \
    ../../src/test-case/model/attributes/attributes-test.cpp \
    ../../src/test-case/model/character-test.cpp \
    ../../src/test-case/model/creation/character-type-model-test.cpp \
    ../../src/test-case/model/exalt/exalt-caste-test.cpp \
    ../../src/test-case/model/power/essence-test.cpp \
    ../../src/test-case/model/power/health-test.cpp \
    ../../src/test-case/model/virtues/virtue-test.cpp \
    ../../src/test-case/model/virtues/virtues-test.cpp



