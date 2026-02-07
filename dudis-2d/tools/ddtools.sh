#!/usr/bin/env bash

target="$1"
args="$2"

if [ -z $target ]; then
    echo "erro faltam argumentos"
    exit 1
fi

if [ $target == "build" ]; then
    ./build_test.sh $args
fi

if [ $target == "run" ]; then
    ./run_test.sh $args
fi

# /tools/build_test.sh all
#   ctest --test-dir tests/build