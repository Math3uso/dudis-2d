#!/usr/bin/env bash

target="$1"

if [ -z "$target" ]; then
    echo "erro faltam argumentos"
    exit 1
fi

shift

if [ "$target" == "build" ]; then
    ./build_test.sh "$@"
elif [ "$target" == "run" ]; then
    ./run_test.sh "$@"
else
    echo "comando desconhecido: $target"
    echo "uso: $0 build|run ..."
    exit 1
fi

# /tools/build_test.sh all
#   ctest --test-dir tests/build
