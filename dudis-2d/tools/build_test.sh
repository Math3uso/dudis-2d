#!/usr/bin/env bash

set -e

usage() {
  echo "Uso: $0 all | unit | platform | smoke | benchmarks | <nome_do_target>"
}

if [ $# -ne 1 ]; then
  usage
  exit 1
fi

arg="$1"
root="$(cd "$(dirname "$0")/.." && pwd)"
tests_dir="$root/tests"
build_dir="$tests_dir/build/unit-debug"
graphics_build_dir="$tests_dir/build/graphics-debug"

if [ ! -f "$tests_dir/CMakeLists.txt" ]; then
  echo "CMakeLists.txt nao encontrado em $tests_dir"
  exit 1
fi

if [ "$arg" = "all" ]; then
  cmake --preset tests-debug "$tests_dir"
  cmake --preset tests-debug-graphics "$tests_dir"
  if cmake --build "$build_dir" && cmake --build "$graphics_build_dir"; then
    echo "Compilacao bem sucedida"
    exit 0
  else
    echo "Compilacao falhou"
    exit 1
  fi
fi

if [ "$arg" = "benchmarks" ]; then
  cmake --preset tests-debug "$tests_dir"
  cmake --build "$build_dir" --target dd_benchmarks
  exit $?
fi

if [ "$arg" = "unit" ] || [ "$arg" = "platform" ] || [ "$arg" = "smoke" ]; then
  preset="tests-debug"
  target_dir="$build_dir"

  if [ "$arg" = "platform" ] || [ "$arg" = "smoke" ]; then
    preset="tests-debug-graphics"
    target_dir="$graphics_build_dir"
  fi

  cmake --preset "$preset" "$tests_dir"

  if cmake --build "$target_dir"; then
    echo "Compilacao bem sucedida"
    exit 0
  fi
  echo "Compilacao falhou"
  exit 1
fi

cmake --preset tests-debug "$tests_dir"

if cmake --build "$build_dir" --target "$arg"; then
  echo "Compilacao bem sucedida"
  exit 0
else
  echo "Compilacao falhou"
  exit 1
fi
