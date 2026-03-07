#!/bin/bash

set -e

# Read opt location
echo "Where is your LLVM opt?"
read opt

# Fresh build
rm -rf ../build/
mkdir ../build
cd ../build
cmake ..
make -j

cd ../examples

# Loop deletion examples
cd loop-deletion
mkdir -p output
rm -f output/*.ll output/*.txt
for cpp_file in *.cpp; do
    [ -e "$cpp_file" ] || continue

    base_name="${cpp_file%.cpp}"

    echo "example: $base_name"

    clang -S -emit-llvm -Xclang -disable-O0-optnone -fno-discard-value-names \
        "$cpp_file" -o "output/${base_name}_output.ll"

    $opt -passes="mem2reg" \
        "output/${base_name}_output.ll" \
        -S -o "output/${base_name}_mem2reg.ll" 2>/dev/null

    $opt -passes="print<loops>" \
        "output/${base_name}_mem2reg.ll" \
        -disable-output 2>&1 | grep "Loop at" || echo "No loops detected"

    $opt \
        -load-pass-plugin=../../build/CustomLoopDeletion/CustomLoopDeletion.so \
        -passes="loop-simplify,lcssa,loop(custom-loop-deletion)" \
        "output/${base_name}_mem2reg.ll" \
        -S -o "output/${base_name}_optimized.ll"


    diff  "output/${base_name}_mem2reg.ll" "output/${base_name}_optimized.ll" || true
    echo "==========================================================================================================================================================================="
done
cd ..

# InstCombine examples
cd instcombine
mkdir -p output
rm -f output/*.ll output/*.txt
for cpp_file in *.cpp; do
    [ -e "$cpp_file" ] || continue

    base_name="${cpp_file%.cpp}"

    echo "example: $base_name"

    clang -S -emit-llvm -Xclang -disable-O0-optnone -fno-discard-value-names \
        "$cpp_file" -o "output/${base_name}_output.ll"

    $opt -passes="mem2reg" \
        "output/${base_name}_output.ll" \
        -S -o "output/${base_name}_mem2reg.ll" 2>/dev/null

    $opt \
        -load-pass-plugin=../../build/MyInstCombine/MyInstCombine.so \
        -passes="my-inst-combine" \
        "output/${base_name}_mem2reg.ll" \
        -S -o "output/${base_name}_optimized.ll"


    diff  "output/${base_name}_mem2reg.ll" "output/${base_name}_optimized.ll" || true
    echo "==========================================================================================================================================================================="
done
cd ..
