// generate_cpp_ir_generator.cpp

#include "llvm_2_cpp_ir_generator.h"

#include <cstdlib>
#include <exception>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <system_error>

int main(const int argc, char* argv[]) {
  if (argc != 3) {
    std::cerr << "Usage: " << argv[0] << " <input.ll> <output.cpp>\n";
    return EXIT_FAILURE;
  }

  if (std::error_code path_error; std::filesystem::equivalent(argv[1], argv[2], path_error)) {
    std::cerr << "Input and output must be different files\n";
    return EXIT_FAILURE;
  }

  std::ofstream output(argv[2]);
  if (!output) {
    std::cerr << "Cannot open " << argv[2] << '\n';
    return EXIT_FAILURE;
  }

  int exit_result = EXIT_SUCCESS;
  try {
    Llvm2CppIrGenerator::generate_ir_generator(argv[1], output);
  } catch (const std::exception& exception) {
    std::cerr << exception.what() << '\n';
    exit_result = EXIT_FAILURE;
  }

  output.close();
  if (!output) {
    std::cerr << "Cannot write " << argv[2] << '\n';
    return EXIT_FAILURE;
  }

  return exit_result;
}
