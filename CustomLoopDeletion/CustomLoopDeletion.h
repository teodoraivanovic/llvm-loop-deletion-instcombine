#ifndef LOOPDELETION_H
#define LOOPDELETION_H

#include "llvm/IR/PassManager.h"
#include "llvm/Analysis/LoopAnalysisManager.h"
#include "llvm/Transforms/Scalar/LoopPassManager.h"

namespace llvm {

    class CustomLoopDeletionPass : public PassInfoMixin<CustomLoopDeletionPass> {
    public:
        PreservedAnalyses run(Loop &L,
                              LoopAnalysisManager &LAM,
                              LoopStandardAnalysisResults &AR,
                              LPMUpdater &Updater);
    private:
        bool isLoopDead(Loop &L, ScalarEvolution &SE);
        bool hasFiniteTripCount(Loop &L, ScalarEvolution &SE);
        bool hasSideEffects(Loop &L);
        bool hasLiveExitValues(Loop &L);
    };

} // namespace llvm

#endif