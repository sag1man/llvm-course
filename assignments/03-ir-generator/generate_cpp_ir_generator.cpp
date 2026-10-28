// generate_cpp_ir_generator.cpp

#include "llvm/Support/FileSystem.h"
#include "llvm_2_cpp_ir_generator.h"

#include <cstdlib>
#include <filesystem>
#include <iostream>

int main(const int argc, char* argv[]) {
  if (argc != 3) {
    std::cerr << "Usage: " << argv[0] << " <input.ll> <output.cpp>\n";
    return EXIT_FAILURE;
  }

  if (std::error_code path_error; std::filesystem::equivalent(argv[1], argv[2], path_error)) {
    std::cerr << "Input and output must be different files\n";
    return EXIT_FAILURE;
  }

  std::error_code error;
  llvm::raw_fd_ostream output(argv[2], error, llvm::sys::fs::OF_Text);
  if (error) {
    std::cerr << "Cannot open " << argv[2] << ": " << error.message() << '\n';
    return EXIT_FAILURE;
  }

  int exit_result = EXIT_SUCCESS;
  try {
    Llvm2CppIrGenerator generator;
    generator.generate(argv[1], output);
  } catch (const std::exception& exception) {
    std::cerr << exception.what() << '\n';
    exit_result = EXIT_FAILURE;
  }

  output.close();
  if (output.has_error()) {
    std::cerr << "Cannot write " << argv[2] << ": " << output.error().message() << '\n';
    output.clear_error();
    return EXIT_FAILURE;
  }

  return exit_result;
}
