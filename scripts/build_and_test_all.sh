#!/bin/bash

set -e

rm -rf ../build/
mkdir ../build
cd ../build
cmake ..
make
cd ../examples

mkdir -p output
rm -f output/*.ll output/*.txt

for cpp_file in *.cpp; do
    [ -e "$cpp_file" ] || continue

    base_name="${cpp_file%.cpp}"

    echo "example: $base_name"

    clang -S -emit-llvm -Xclang -disable-O0-optnone -fno-discard-value-names \
        "$cpp_file" -o "output/${base_name}_output.ll"

    /usr/lib/llvm-13/bin/opt -passes="mem2reg" \
        "output/${base_name}_output.ll" \
        -S -o "output/${base_name}_mem2reg.ll" 2>/dev/null

    /usr/lib/llvm-13/bin/opt -passes="print<loops>" \
        "output/${base_name}_mem2reg.ll" \
        -disable-output 2>&1 | grep "Loop at" || echo "No loops detected"

    /usr/lib/llvm-13/bin/opt \
        -load-pass-plugin=../build/CustomLoopDeletion/CustomLoopDeletion.so \
        -passes="loop-simplify,lcssa,loop(custom-loop-deletion)" \
        "output/${base_name}_mem2reg.ll" \
        -S -o "output/${base_name}_optimized.ll"


    diff  "output/${base_name}_mem2reg.ll" "output/${base_name}_optimized.ll" || true
    echo "======================================================================================"
done