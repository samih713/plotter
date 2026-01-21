#!/usr/bin/env bash

mode="${1,,}"   # lowercase $1 (bash 4+)

CXXFLAGS=(-Wall -Wextra -Werror)
if [[ "$mode" == "debug" ]]; then
    CXXFLAGS+=(-fsanitize=undefined -ggdb3)
elif [[ "$mode" == "release" ]]; then
    CXXFLAGS+=(-O3)
fi

LIBS="-lm -lraylib"
EXECUTABLE="./build/plotter"
INCLUDES="-I./includes -I./ -I./srcs"
SRCS="srcs/App.cpp srcs/Renderer.cpp srcs/Series.cpp  main.cpp"

set -e

(
    set -x
    clang++ "${CXXFLAGS[@]}" ${INCLUDES} ${SRCS} -o ${EXECUTABLE} ${LIBS}
) 

if [[ "${2}" == "run" ]]; then
    echo "running ... "
    ./${EXECUTABLE}
fi


