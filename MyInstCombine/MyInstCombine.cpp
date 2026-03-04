#include "llvm/IR/PatternMatch.h"
#include "llvm/Pass.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Passes/PassPlugin.h"

#include <algorithm>
#include <vector>

using namespace llvm;
using namespace llvm::PatternMatch;

namespace {

struct MyInstCombine : public PassInfoMixin<MyInstCombine> {

    static bool replace_instruction(Instruction &I, Value *V) {
        if (V == &I)
            return false;

        I.replaceAllUsesWith(V);
        I.eraseFromParent();

        return true;
    }

    static bool arithmetic(Instruction &I) {
        auto *BO = dyn_cast<BinaryOperator>(&I);
        if (!BO)
            return false;
        Value *X = nullptr;

        // X + 0 = 0 + X = X
        if (match(BO, m_Add(m_Value(X), m_Zero())) ||
            match(BO, m_Add(m_Zero(), m_Value(X))))
            return replace_instruction(I, X);

        // X - 0 = X
        if (match(BO, m_Sub(m_Value(X), m_Zero())))
            return replace_instruction(I, X);

        // X * 1 = 1 * X = X
        if (match(BO, m_Mul(m_Value(X), m_One())) ||
            match(BO, m_Mul(m_One(), m_Value(X))))
            return replace_instruction(I, X);

        // X * 0 = 0 * X = 0
        if (match(BO, m_Mul(m_Value(X), m_Zero())) ||
            match(BO, m_Mul(m_Zero(), m_Value(X))))
            return replace_instruction(I, Constant::getNullValue(I.getType()));

        // X && 1....1 = 1...1 && X = X
        if (match(BO, m_And(m_Value(X), m_AllOnes())) ||
            match(BO, m_And(m_AllOnes(), m_Value(X))))
            return replace_instruction(I, X);

        // X || 0 = 0 || X = X
        if (match(BO, m_Or(m_Value(X), m_Zero())) ||
            match(BO, m_Or(m_Zero(), m_Value(X))))
            return replace_instruction(I, X);

        // X xor 0 = X
        if (match(BO, m_Xor(m_Value(X), m_Zero())) ||
            match(BO, m_Xor(m_Zero(), m_Value(X))))
            return replace_instruction(I, X);

        // X xor X = X - X = 0
        if (match(BO, m_Xor(m_Value(X), m_Specific(X))) ||
            match(BO, m_Sub(m_Value(X), m_Specific(X))))
            return replace_instruction(I, Constant::getNullValue(I.getType()));

        return false;
    }

    bool apply(Instruction &I) {
        auto optimizations = {arithmetic};

        for (auto &O : optimizations) {
            if (O(I))
                return true;
        }

        return false;
    }

    bool run(Function &F) {
        bool changed = false;
        bool local_changed = true;
        unsigned iteration = 0;
        const unsigned MAX_ITERATIONS = 100;

        while (local_changed && iteration < MAX_ITERATIONS) {
            local_changed = false;
            ++iteration;

            std::vector<Instruction *> instructions;
            for (BasicBlock &BB : F) {
                for (Instruction &I : BB) {
                    instructions.push_back(&I);
                }
            }

            for (unsigned i = 0; i < instructions.size(); ++i) {
                Instruction *I = instructions[i];

                if (!I || !I->getParent())
                    continue;

                std::vector<Instruction *> users;
                for (User *U : I->users()) {
                    if (auto *UI = dyn_cast<Instruction>(U)) {
                        users.push_back(UI);
                    }
                }

                bool changed = apply(*I);
                local_changed |= changed;

                if (changed) {
                    for (Instruction *UI : users) {
                        if (UI->getParent()) {
                            if (std::find(instructions.begin() + i + 1,
                                          instructions.end(),
                                          UI) == instructions.end()) {
                                instructions.push_back(UI);
                            }
                        }
                    }
                }
            }

            changed |= local_changed;
        }

        return changed;
    }

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
