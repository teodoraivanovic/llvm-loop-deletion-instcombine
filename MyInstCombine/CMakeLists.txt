add_llvm_pass_plugin(MyInstCombine
    MyInstCombine.cpp
)

target_link_libraries(MyInstCombine PRIVATE LLVM)
