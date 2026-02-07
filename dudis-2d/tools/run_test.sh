#!/usr/bin/env bash

arg="$1"

if [ -z "$arg" ]; then
    echo "Uso: $0 | test-name || all"
    exit 1
fi

cd ../tests/build/"$arg"

if [ "$(uname)" == "Linux" ]; then
    ./"$arg"
    exit 0

elif [[ "$(uname)" == *"MSYS"* || "$(uname)" == *"Windows"* ]]; then
    ./"$arg.exe"
    exit 0
else
    echo "Sistema operacional não reconhecido: $(uname)"
    exit 1
fi