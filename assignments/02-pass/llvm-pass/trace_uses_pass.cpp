// trace_users.cpp

#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Verifier.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Passes/PassPlugin.h"
#include "llvm/Support/ErrorHandling.h"

#include <array>

using namespace llvm;

namespace {

class TraceUsesPass : public PassInfoMixin<TraceUsesPass> {
  static void insertUsesLog(Function& function, const FunctionCallee logger, IRBuilder<>& builder) {
    for (auto& basic_block : function) {
      for (auto& instruction : basic_block) {
        if (isa<PHINode>(instruction)) {
          continue;
        }

        builder.SetInsertPoint(&instruction);

        for (auto& use : instruction.operands()) {
          Value* operand = use.get();
          const auto* producer = dyn_cast<Instruction>(operand);

          if (producer == nullptr) {
            continue;
          }

          const std::array<Value*, 2> args = {
              builder.getInt32(instruction.getOpcode()),
              builder.getInt32(producer->getOpcode()),
          };

          builder.CreateCall(logger, args);
        }
      }
    }
  }

public:
  [[maybe_unused]] static PreservedAnalyses run(Module& module, ModuleAnalysisManager& /*unused*/) {
    LLVMContext& context = module.getContext();
    IRBuilder<> builder(context);

    Type* void_type = Type::getVoidTy(context);
    Type* int32_type = Type::getInt32Ty(context);

    const std::array<Type*, 2> param_types = {int32_type, int32_type};
    FunctionType* logger_type = FunctionType::get(void_type, param_types, false);

    const FunctionCallee logger = module.getOrInsertFunction("trace_use", logger_type);

    for (auto& function : module) {
      if (function.isDeclaration()) {
        continue;
      }

      insertUsesLog(function, logger, builder);
    }

    if (verifyModule(module, &errs())) {
      report_fatal_error("TraceUses: invalid IR after instrumentation");
    }

    return PreservedAnalyses::none();
  }
};

PassPluginLibraryInfo getPassPluginInfo() {
  const auto callback = [](PassBuilder& pass_builder) {
    pass_builder.registerOptimizerLastEPCallback([](ModulePassManager& module_pass_manager, OptimizationLevel) {
      module_pass_manager.addPass(TraceUsesPass{});
    });
  };

  return {
      .APIVersion = LLVM_PLUGIN_API_VERSION,
      .PluginName = "TraceUses",
      .PluginVersion = "0.0.1",
      .RegisterPassBuilderCallbacks = callback,
  };
}

} // namespace

extern "C" LLVM_ATTRIBUTE_WEAK PassPluginLibraryInfo llvmGetPassPluginInfo() {
  return getPassPluginInfo();
}
