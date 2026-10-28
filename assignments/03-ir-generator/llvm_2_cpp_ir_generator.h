// llvm_2_cpp_ir_generator.h

#pragma once

#include "llvm/IR/Module.h"
#include "llvm/Support/raw_ostream.h"

#include <string>

class Llvm2CppIrGenerator {
public:
  void generate(const std::string& input_path, llvm::raw_ostream& output);
  void generate(const llvm::Module& module, llvm::raw_ostream& output);
};

