// llvm_2_cpp_ir_generator.h

#pragma once

#include "llvm/IR/Module.h"

#include <string>
#include <unordered_set>

class Llvm2CppIrGenerator {
public:
  static void generate_ir_generator(const std::string& input_path, std::ostream& output);
  static void generate_ir_generator(const llvm::Module& module, std::ostream& output);

private:
  static void collect_types_and_functions_to_define(
      const llvm::Module& module,
      std::unordered_set<const llvm::Type*> types,
      std::vector<const llvm::Function*> functions_to_define
  );
  static void emit_header(std::ostream& output);
  static void emit_declare_functions(const llvm::Module& module, std::ostream& output);
  static void emit_define_function(const llvm::Function& function, std::ostream& output);
  static void emit_footer(std::ostream& output);

  static void emit_type(const llvm::Type& type, std::ostream& output);
  static std::string get_type_name(const llvm::Type& type);
  static std::string get_type_expression(const llvm::Type& type);
};
