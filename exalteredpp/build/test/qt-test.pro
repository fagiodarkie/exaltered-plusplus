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
    ../../headers/calculator \
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
    ../../headers/calculator/experience_purchase_cost_calculator.h \
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
    ../../headers/model/abilities/abilities.h \
    ../../headers/model/abilities/ability.h \
    ../../headers/model/abilities/ability_group.h \
    ../../headers/model/abilities/ability.h \
    ../../headers/model/abilities/abstract_ability_factory.h \
    ../../headers/model/abilities/specialisation.h \
    ../../headers/model/attributes/attribute.h \
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
    ../../headers/model/power/power_container.h \
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
    ../../headers/qt-test/quick_chargen.h \
    ../../headers/serialisation/db_abstraction.h \
    ../../headers/serialisation/filesystem_db.h \
    ../../headers/serialisation/json_constants.h \
    ../../headers/serialisation/serialisable.h \
    ../../headers/test-case/db_abstraction_mock.h \
    ../../thirdparty/catch/catch.hpp \
    ../../thirdparty/serialisable/serialisable.hpp

SOURCES += \
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
    ../../src/errors/ability_not_found_exception.cpp \
    ../../src/errors/characternotfoundexception.cpp \
    ../../src/errors/invalid_parameter.cpp \
    ../../src/model/abilities/abilities.cpp \
    ../../src/model/abilities/ability.cpp \
    ../../src/model/abilities/ability_group.cpp \
    ../../src/model/abilities/specialisation.cpp \
    ../../src/model/attributes/attribute.cpp \
    ../../src/model/attributes/attributes.cpp \
    ../../src/model/character/character.cpp \
    ../../src/model/character/creation/character_creation_configuration.cpp \
    ../../src/model/character/creation/character_type_model.cpp \
    ../../src/model/character/exalt/exalt_caste.cpp \
    ../../src/model/character/exalt/exalt_caste_abilities.cpp \
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
    ../../src/model/power/power_container.cpp \
    ../../src/model/power/willpower.cpp \
    ../../src/model/social/persona.cpp \
    ../../src/model/social/philosophy.cpp \
    ../../src/model/virtues/virtue.cpp \
    ../../src/model/virtues/virtues.cpp \
    ../../src/model/managers/character_manager.cpp \
    ../../src/qt-test/main.cpp \
    ../../src/qt-test/quick_chargen.cpp \
    ../../src/serialisation/filesystem_db.cpp \
    ../../src/serialisation/json_constants.cpp \
    ../../src/test-case/calculator/worker/common-worker-test.cpp \
    ../../src/test-case/common/reverse-search-tests.cpp \
    ../../src/test-case/errors/exceptions-test.cpp \
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
    ../../src/test-case/model/narrative/ability_purchase-test.cpp \
    ../../src/test-case/model/narrative/specialisation_purchase-test.cpp \
    ../../src/test-case/model/power/essence-test.cpp \
    ../../src/test-case/model/power/health-test.cpp \
    ../../src/test-case/model/power/logos-test.cpp \
    ../../src/test-case/model/power/power-container-test.cpp \
    ../../src/test-case/model/power/willpower-test.cpp \
    ../../src/test-case/model/social/persona-test.cpp \
    ../../src/test-case/model/social/philosophy-test.cpp \
    ../../src/test-case/model/virtues/virtue-test.cpp \
    ../../src/test-case/model/virtues/virtues-test.cpp




