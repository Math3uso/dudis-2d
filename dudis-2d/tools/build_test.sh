#!/usr/bin/env bash

set -e

usage() {
  echo "Uso: $0 all | <nome_do_teste>"
}

if [ $# -ne 1 ]; then
  usage
  exit 1
fi

arg="$1"
root="$(cd "$(dirname "$0")/.." && pwd)"
tests_dir="$root/tests"
build_dir="$tests_dir/build"

if [ ! -f "$tests_dir/CMakeLists.txt" ]; then
  echo "CMakeLists.txt nao encontrado em $tests_dir"
  exit 1
fi

cmake -S "$tests_dir" -B "$build_dir"

if [ "$arg" = "all" ]; then
  if cmake --build "$build_dir"; then
    echo "Compilacao bem sucedida"
    exit 0
  else
    echo "Compilacao falhou"
    exit 1
  fi
fi

if [ ! -d "$tests_dir/$arg" ]; then
  usage
  exit 1
fi

if cmake --build "$build_dir" --target "$arg"; then
  echo "Compilacao bem sucedida"
  exit 0
else
  echo "Compilacao falhou"
  exit 1
fi
