#!/bin/bash

set -e

CLANG_FORMAT_PATH=$(which clang-format 2> /dev/null)

if [ -z "$CLANG_FORMAT_PATH" ]; then
    echo "Error: \`clang-format\` not available, can't format files"
    exit 1
fi

find LoopDeletion | grep -E '\.(cpp|hpp)$' | \
  parallel --jobs "$(nproc)" "clang-format -i"