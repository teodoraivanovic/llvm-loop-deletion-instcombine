add_library(LoopDeletion MODULE
        LoopDeletion.cpp
        LoopDeletion.h
)

target_compile_features(LoopDeletion PRIVATE cxx_std_20)

set_target_properties(LoopDeletion PROPERTIES
        COMPILE_FLAGS "-fno-rtti"
)