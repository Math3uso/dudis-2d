#!/usr/bin/env bash

arg="$1"
shift || true

if [ -z "$arg" ]; then
    echo "Uso: $0 all | unit | platform | smoke | benchmarks | <nome_do_target> [filtro_do_catch2] [args_do_catch2...]"
    exit 1
fi

root="$(cd "$(dirname "$0")/.." && pwd)"
build_dir="$root/tests/build/unit-debug"
graphics_build_dir="$root/tests/build/graphics-debug"
bin_dir="$build_dir/bin"

resolve_test_binary() {
    local target="$1"
    local ext=""

    if [[ "$(uname)" == *"MSYS"* || "$(uname)" == *"Windows"* ]]; then
        ext=".exe"
    fi

    if [ -x "$bin_dir/$target$ext" ]; then
        echo "$bin_dir/$target$ext"
        return 0
    fi

    if [ -x "$graphics_build_dir/bin/$target$ext" ]; then
        echo "$graphics_build_dir/bin/$target$ext"
        return 0
    fi

    return 1
}

list_test_names() {
    local binary="$1"

    (cd "$root/tests" && "$binary" --list-tests) | awk '
        /^  [^ ]/ {
            name = $0
            sub(/^  /, "", name)
            print name
        }
    '
}

print_indexed_tests() {
    local binary="$1"

    list_test_names "$binary" | awk '{ print NR - 1 " - " $0 }'
}

is_number() {
    [[ "$1" =~ ^[0-9]+$ ]]
}

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

if ! binary="$(resolve_test_binary "$arg")"; then
    echo "Target de teste nao encontrado: $arg"
    exit 1
fi

if [ $# -eq 0 ] || [ "$1" = "list" ] || [ "$1" = "--list" ]; then
    print_indexed_tests "$binary"
    exit $?
fi

if [ "$1" = "--all-tests" ]; then
    shift
    (cd "$root/tests" && "$binary" "$@")
    exit $?
fi

if is_number "$1"; then
    index="$1"
    shift
    test_name="$(list_test_names "$binary" | awk -v wanted="$index" 'NR - 1 == wanted { print; found = 1 } END { exit found ? 0 : 1 }')"

    if [ -z "$test_name" ]; then
        echo "Indice de teste invalido: $index"
        echo
        print_indexed_tests "$binary"
        exit 1
    fi

    (cd "$root/tests" && "$binary" "$test_name" "$@")
    exit $?
fi

(cd "$root/tests" && "$binary" "$@")
exit $?
