#!/bin/bash

set -e

shopt -s nullglob

rm -f examples/*.ll

for file in examples/*.cpp; do
  clang -S -emit-llvm -Xclang -disable-O0-optnone -fno-discard-value-names "$file" -o "${file%.cpp}.ll"
done