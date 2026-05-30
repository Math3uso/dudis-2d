#!/usr/bin/env bash

arg="$1"

if [ -z "$arg" ]; then
    echo "Uso: $0 all | unit | platform | smoke | benchmarks | <nome_do_target>"
    exit 1
fi

root="$(cd "$(dirname "$0")/.." && pwd)"
build_dir="$root/tests/build/unit-debug"
graphics_build_dir="$root/tests/build/graphics-debug"
bin_dir="$build_dir/bin"

if [ "$arg" = "all" ]; then
    ctest --test-dir "$build_dir" --output-on-failure
    unit_status=$?
    ctest --test-dir "$graphics_build_dir" --output-on-failure
    graphics_status=$?
    if [ "$unit_status" -ne 0 ]; then
        exit "$unit_status"
    fi
    exit "$graphics_status"
fi

if [ "$arg" = "platform" ]; then
    ctest --test-dir "$graphics_build_dir" -L "$arg" --output-on-failure
    exit $?
fi

if [ "$arg" = "unit" ] || [ "$arg" = "smoke" ]; then
    selected_build_dir="$build_dir"

    if [ "$arg" = "smoke" ]; then
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
    if [ -x "$bin_dir/$arg" ]; then
        "$bin_dir/$arg"
    else
        "$graphics_build_dir/bin/$arg"
    fi
    exit 0

elif [[ "$(uname)" == *"MSYS"* || "$(uname)" == *"Windows"* ]]; then
    if [ -x "$bin_dir/$arg.exe" ]; then
        "$bin_dir/$arg.exe"
    else
        "$graphics_build_dir/bin/$arg.exe"
    fi
    exit 0
else
    echo "Sistema operacional não reconhecido: $(uname)"
    exit 1
fi
