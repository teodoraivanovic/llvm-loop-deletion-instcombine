add_llvm_pass_plugin(CustomLoopDeletion
        CustomLoopDeletion.cpp
)

target_link_libraries(CustomLoopDeletion PRIVATE LLVM)
