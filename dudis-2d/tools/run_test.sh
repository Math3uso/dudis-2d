#!/usr/bin/env bash

arg="$1"

if [ -z "$arg" ]; then
    echo "Uso: $0 all | unit | smoke | visual | benchmarks | <nome_do_target>"
    exit 1
fi

root="$(cd "$(dirname "$0")/.." && pwd)"
build_dir="$root/tests/build/unit-debug"
graphics_build_dir="$root/tests/build/graphics-debug"
bin_dir="$build_dir/bin"

if [ "$arg" = "all" ]; then
    ctest --test-dir "$build_dir" --output-on-failure
    exit $?
fi

if [ "$arg" = "unit" ] || [ "$arg" = "smoke" ] || [ "$arg" = "visual" ]; then
    selected_build_dir="$build_dir"

    if [ "$arg" = "smoke" ] || [ "$arg" = "visual" ]; then
        selected_build_dir="$graphics_build_dir"
    fi

    ctest --test-dir "$selected_build_dir" -L "$arg" --output-on-failure
    exit $?
fi

if [ "$arg" = "benchmarks" ]; then
    "$bin_dir/scene_benchmark"
    exit $?
fi

if [ "$(uname)" == "Linux" ]; then
    "$bin_dir/$arg"
    exit 0

elif [[ "$(uname)" == *"MSYS"* || "$(uname)" == *"Windows"* ]]; then
    "$bin_dir/$arg.exe"
    exit 0
else
    echo "Sistema operacional não reconhecido: $(uname)"
    exit 1
fi
