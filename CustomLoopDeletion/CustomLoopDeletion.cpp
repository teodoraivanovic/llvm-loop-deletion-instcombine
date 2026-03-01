#include "CustomLoopDeletion.h"
#include "llvm/Analysis/LoopInfo.h"
#include "llvm/Analysis/ScalarEvolution.h"
#include "llvm/IR/Dominators.h"
#include "llvm/IR/Instructions.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Passes/PassPlugin.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Transforms/Scalar/LoopPassManager.h"
#include "llvm/Transforms/Utils/LoopUtils.h"
#include "llvm/Transforms/Utils/BasicBlockUtils.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/CFG.h"
#include "llvm/Analysis/ValueTracking.h"

using namespace llvm;

PreservedAnalyses CustomLoopDeletionPass::run(
    Loop &L,
    LoopAnalysisManager &LAM,
    LoopStandardAnalysisResults &AR,
    LPMUpdater &Updater) {

    errs() << "===========================================================================================================================================================================\n";
    errs() << "CUSTOM LOOP DELETION PASS RUNNING\n";
    errs() << "===========================================================================================================================================================================\n";

    ScalarEvolution &SE = AR.SE;
    LoopInfo &LI = AR.LI;
    DominatorTree &DT = AR.DT;

    if (!isLoopDead(L, SE)) {
        errs() << "Loop is ALIVE\n";
        errs() << "===========================================================================================================================================================================\n";
        return PreservedAnalyses::all();
    }

    errs() << "Deleting safely...\n";
	errs() << "===========================================================================================================================================================================\n";

    // delete the loop safely using llvm's function
    std::string loopName = L.getName().str();
    deleteDeadLoop(&L, &DT, &SE, &LI, nullptr);
    Updater.markLoopAsDeleted(L, loopName);

    return PreservedAnalyses::none();
}

// all three must be satisfied:
// - finite trip count
// - no side effects
// - no live exit values
bool CustomLoopDeletionPass::isLoopDead(Loop &L, ScalarEvolution &SE) {
    errs() << "Checking if loop is dead...\n";

    if (!hasFiniteTripCount(L, SE)) {
        errs() << "*** No finite trip count\n";
        return false;
    } else {
        errs() << "*** Finite trip count\n";
	}

    if (hasSideEffects(L)) {
        errs() << "*** Has side effects\n";
        return false;
    } else {
	    errs() << "*** Doesn't have side effects\n";
	}

    if (hasLiveExitValues(L)) {
        errs() << "*** Has live exit values\n";
        return false;
    } else {
		errs() << "*** Doesn't have live exit values\n";
	}

    errs() << "Loop is DEAD!\n";
    return true;
}

bool CustomLoopDeletionPass::hasFiniteTripCount(Loop &L, ScalarEvolution &SE) {
    const SCEV *BECount = SE.getBackedgeTakenCount(&L);

    // can't calculate trip count - possibly infinite
    if (isa<SCEVCouldNotCompute>(BECount)) {
        return false;
    }

    errs() << "*** Trip count: " << *BECount << "\n";
    return true;
}

bool CustomLoopDeletionPass::hasSideEffects(Loop &L) {
    for (BasicBlock *BB : L.blocks()) {
        for (Instruction &I : *BB) {

            // skip PHI nodes and branches
            if (isa<PHINode>(&I) || isa<BranchInst>(&I))
                continue;

            if (auto *SI = dyn_cast<StoreInst>(&I)) {

                // volatile stores are ALWAYS side effects
                if (SI->isVolatile()) {
                    errs() << "*** Side effect (volatile store): " << I << "\n";
                    return true;
                }

                Value *Ptr = SI->getPointerOperand();

                // "underlying object" - separate allocated memory region that a pointer is based on
                Value *Base = getUnderlyingObject(Ptr);

                // if base is a local alloca => safe
                if (isa<AllocaInst>(Base)) {
                    errs() << "*** Has a local store, but values are not used outside of the loop\n";
                    continue;
                }

                // if it's not a local store => side effect
                errs() << "*** Side effect (escaping store): " << I << "\n";
                return true;
            }

            // if it's a call, check for side effects
            if (auto *CI = dyn_cast<CallBase>(&I)) {
                if (!CI->onlyReadsMemory()) {
                    errs() << "*** Call with side effects: " << I << "\n";
                    return true;
                }
                continue;
            }

            // check for any other instruction
            if (I.mayHaveSideEffects()) {
                errs() << "*** Side effect: " << I << "\n";
                return true;
            }
        }
    }
    return false;
}

bool CustomLoopDeletionPass::hasLiveExitValues(Loop &L) {
    for (BasicBlock *BB : L.blocks()) {
        for (Instruction &I : *BB) {

            // skip terminators such as br, ret, conditional branches etc
            if (I.isTerminator())
                continue;

            // iterate over all uses of the instruction
            for (Use &U : I.uses()) {
                if (Instruction *User = dyn_cast<Instruction>(U.getUser())) { // if it's not a real instruction but a constant for example

                    if (!L.contains(User->getParent())) {
                        errs() << "*** Live value escapes: " << I << "\n";
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

// plugin registration
extern "C" LLVM_ATTRIBUTE_WEAK ::llvm::PassPluginLibraryInfo
llvmGetPassPluginInfo() {
    return {
        LLVM_PLUGIN_API_VERSION,
        "CustomLoopDeletion",
        LLVM_VERSION_STRING,
        [](PassBuilder &PB) {

            // Register as a LOOP PASS with UNIQUE (!!!) name
            PB.registerPipelineParsingCallback(
                [](StringRef Name, LoopPassManager &LPM,
                   ArrayRef<PassBuilder::PipelineElement>) {

                    if (Name == "custom-loop-deletion") {
                        errs() << "===========================================================================================================================================================================\n";
                        errs() << "Adding CustomLoopDeletionPass...\n";
                        LPM.addPass(CustomLoopDeletionPass());
                        return true;
                    }

                    return false;
                });
        }
    };
}