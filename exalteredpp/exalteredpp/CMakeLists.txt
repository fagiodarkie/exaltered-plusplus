# CMakeList.txt: progetto CMake per exalteredpp. Includere l'origine e definire
# qui la logica specifica del progetto.
#
cmake_minimum_required (VERSION 3.8)

include_directories("headers"
"headers/character" "headers/character/attributes"
"headers/utilities")

set(CHARACTER_SOURCES "headers/character/character.h" "src/character/character.cpp")

set(SOURCES "exalteredpp.h" ${CHARACTER_SOURCES})

# Aggiungere l'origine all'eseguibile di questo progetto.
add_executable (exalteredpp "exalteredpp.cpp" ${SOURCES})

# TODO: Aggiungere i test e, se necessario, installare le destinazioni.
