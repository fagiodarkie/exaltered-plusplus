cmake_minimum_required (VERSION 3.8)

# header folders
set(HEADER_FOLDERS "headers"
	"headers/character" "headers/character/attributes"
	)

include_directories(${HEADER_FOLDERS})

#test header folders
#set(TEST_HEADER_FILES "")
set(TEST_HEADERS "thirdparty/catch/catch.hpp"
	#${TEST_HEADER_FILES
	)

# character classes
set(ATTRIBUTE_SOURCES "headers/character/attributes/attributes.h" "headers/character/attributes/attributeNames.h" "src/character/attributes/attributes.cpp")
set(CHARACTER_SOURCES "headers/character/character.h" "src/character/character.cpp" ${ATTRIBUTE_SOURCES})

# main project sources
set(PROJECT_SOURCES ${CHARACTER_SOURCES})

# application sources
set(APP_SOURCES "exalteredpp.cpp" "exalteredpp.h"
	${PROJECT_SOURCES}
	)

# test cases
set(TEST_CASE_SOURCES "test-case/attribute-test.cpp")

# test application sources
set(TEST_SOURCES "exaltered-test.cpp"
	${TEST_CASE_SOURCES}
	${PROJECT_SOURCES}
	)

# targets
add_executable (exalteredpp ${APP_SOURCES})

add_executable (tests ${TEST_SOURCES})