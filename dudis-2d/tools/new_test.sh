#!/usr/bin/env sh

cd ../

NAME=$1
SUITE=$2

if [ -z "$NAME" ]; then
  echo "Uso: new-test <nome> [unit|smoke|visual]"
  exit 1
fi

if [ -z "$SUITE" ]; then
  SUITE="unit"
fi

DIR="tests/$SUITE/$NAME"

mkdir -p "$DIR"

cd "$DIR"

cat << EOF2 > CMakeLists.txt
dd_add_suite_test(${NAME} ${SUITE}
  SOURCES
    ${NAME}.test.cpp
)
EOF2

cat << EOF2 > ${1}.test.cpp
#include <catch2/catch_test_macros.hpp>

#include "support/test_context.h"

TEST_CASE("$NAME test", "[$SUITE]")
{
    REQUIRE(true);
}
EOF2
