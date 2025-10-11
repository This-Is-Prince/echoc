#!/bin/sh

set -e

(
    cd "$(dirname "$0")"
    rm -rf build
    mkdir build
    gcc ./src/main.c -o ./build/main
)

exec ./build/main "$@"