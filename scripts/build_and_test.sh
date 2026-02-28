#!/bin/bash

set -e

rm -rf ../build/
mkdir ../build
cd ../build
cmake -DCMAKE_BUILD_TYPE=Debug ..
make

cd ../examples

clang -S -emit-llvm -Xclang -disable-O0-optnone -fno-discard-value-names 01_dead_loop.cpp -o 01_output.ll

/usr/lib/llvm-13/bin/opt -passes="mem2reg" 01_output.ll -S -o 01_mem2reg.ll 2>/dev/null

/usr/lib/llvm-13/bin/opt -passes="print<loops>" 01_mem2reg.ll -disable-output 2>&1 | grep "Loop at"

echo "======================================================================================"
echo "RUN THE PASSES"
echo "======================================================================================"

/usr/lib/llvm-13/bin/opt -load-pass-plugin=../build/CustomLoopDeletion/CustomLoopDeletion.so \
  -passes="loop-simplify,lcssa,loop(custom-loop-deletion)" \
  01_mem2reg.ll -S -o 01_optimized.ll
  #-debug-pass-manager

echo "======================================================================================"
echo "COMPARE THE FILES"
echo "======================================================================================"

diff 01_mem2reg.ll 01_optimized.ll