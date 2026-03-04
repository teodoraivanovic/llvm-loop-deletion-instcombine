#include "llvm/Pass.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Passes/PassPlugin.h"

using namespace llvm;

namespace {

struct MyInstCombine : public PassInfoMixin<MyInstCombine> {

    bool run(Function &F) { return false; }

    PreservedAnalyses run(Function &F, FunctionAnalysisManager &AM) {
        bool changed = run(F);
        return changed ? PreservedAnalyses::none() : PreservedAnalyses::all();
    }
};

} // namespace

extern "C" LLVM_ATTRIBUTE_WEAK ::llvm::PassPluginLibraryInfo
llvmGetPassPluginInfo() {
    return {LLVM_PLUGIN_API_VERSION, "MyInstCombine", LLVM_VERSION_STRING,
            [](PassBuilder &PB) {
                PB.registerPipelineParsingCallback(
                    [](StringRef Name, FunctionPassManager &FPM,
                       ArrayRef<PassBuilder::PipelineElement>) {
                        if (Name == "my-inst-combine") {
                            FPM.addPass(MyInstCombine());
                            return true;
                        }
                        return false;
                    });
            }};
}
