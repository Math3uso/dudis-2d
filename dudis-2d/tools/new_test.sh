#!/usr/bin/env sh

cd ../
ROOT=$(pwd)

NAME=$1
SUITE=$2

if [ -z "$NAME" ]; then
  echo "Uso: new-test <nome> [unit|platform|smoke]"
  exit 1
fi

if [ -z "$SUITE" ]; then
  SUITE="unit"
fi

case "$SUITE" in
  unit|platform|smoke) ;;
  *)
    echo "Categoria invalida: $SUITE"
    echo "Uso: new-test <nome> [unit|platform|smoke]"
    exit 1
    ;;
esac

DIR="tests/$SUITE/$NAME"
TARGET_NAME=$(printf "%s_%s" "$NAME" "$SUITE" | tr '/-' '__')
SOURCE_FILE="$(basename "$NAME").test.cpp"
SOURCE_PATH="$SUITE/$NAME/$SOURCE_FILE"

mkdir -p "$DIR"

cd "$DIR"

TEST_SUPPORT_INCLUDE="support/test_context.h"
if [ "$SUITE" = "platform" ]; then
  TEST_SUPPORT_INCLUDE="support/platform_test_context.h"
fi

cat << EOF2 > "$SOURCE_FILE"
#include <catch2/catch_test_macros.hpp>

#include "$TEST_SUPPORT_INCLUDE"

TEST_CASE("$NAME test", "[$SUITE]")
{
    REQUIRE(true);
}
EOF2

cd "$ROOT"

if ! grep -q "dd_add_test(${TARGET_NAME}" tests/CMakeLists.txt; then
  cat << EOF2 >> tests/CMakeLists.txt

dd_add_test(${TARGET_NAME}
  SUITE ${SUITE}
  SOURCES
    ${SOURCE_PATH}
)
EOF2
fi
