#!/usr/bin/env sh

cd ../

NAME=$1

if [ -z "$NAME" ]; then
  echo "Uso: new-test <nome>"
  exit 1
fi

DIR="tests/$NAME"

mkdir -p "$DIR"

cd "$DIR"

cat << EOF2 > CMakeLists.txt
dd_add_test("$NAME")
EOF2

cat << EOF2 > ${1}.test.cpp
#include <catch2/catch_test_macros.hpp>

#include "dudis2d/dudis2d.h"

TEST_CASE("$NAME test")
{
    REQUIRE(true);
}
EOF2
