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

cat << EOF > CMakeLists.txt
add_executable("$NAME" "$NAME".test.cpp)

target_link_libraries("$NAME" PRIVATE dudis)

target_include_directories("$NAME" PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/../../include
)
EOF

cat << EOF > ${1}.test.cpp
#include "dudis2d/dudis2d.h"

int main()
{
    return 0;
}
EOF
