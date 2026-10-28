cmake_minimum_required(VERSION 3.20)
project(llvm_course LANGUAGES C CXX)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# LLVM Pass
find_package(LLVM 18.1 REQUIRED CONFIG)

list(APPEND CMAKE_MODULE_PATH "${LLVM_CMAKE_DIR}")
include(AddLLVM)

add_llvm_pass_plugin(TraceUses assignments/02-pass/llvm-pass/trace_uses_pass.cpp)

target_include_directories(TraceUses SYSTEM PRIVATE ${LLVM_INCLUDE_DIRS})

separate_arguments(LLVM_DEFINITIONS_LIST NATIVE_COMMAND "${LLVM_DEFINITIONS}")
target_compile_options(TraceUses PRIVATE ${LLVM_DEFINITIONS_LIST})

# Analyzer
add_library(trace_runtime STATIC
        assignments/02-pass/runtime/trace.cpp
        assignments/02-pass/runtime/trace.h
        assignments/02-pass/runtime/trace_analyzer.cpp
        assignments/02-pass/runtime/trace_analyzer.h)

target_include_directories(trace_runtime SYSTEM PRIVATE ${LLVM_INCLUDE_DIRS})
target_compile_options(trace_runtime PRIVATE ${LLVM_DEFINITIONS_LIST})
target_link_libraries(trace_runtime PUBLIC LLVM)
target_compile_options(trace_runtime PRIVATE -O2)
target_include_directories(trace_runtime PUBLIC assignments/02-pass/runtime)

# Graphic app
find_package(PkgConfig REQUIRED)
pkg_check_modules(SDL2 REQUIRED IMPORTED_TARGET sdl2)

add_executable(graphics
        assignments/01-graphics/app.c
        lib/sim/start.c
        lib/sim/sim.c)

target_include_directories(graphics PRIVATE lib/sim)
target_link_libraries(graphics PRIVATE PkgConfig::SDL2)

# IR generator generator
add_executable(generate_cpp_ir_generator
        assignments/03-ir-generator/generator/generate_cpp_ir_generator.cpp
        assignments/03-ir-generator/generator/llvm_2_cpp_ir_generator.cpp
        assignments/03-ir-generator/generator/llvm_2_cpp_ir_generator.h)

target_include_directories(generate_cpp_ir_generator SYSTEM PRIVATE ${LLVM_INCLUDE_DIRS})
target_compile_options(generate_cpp_ir_generator PRIVATE ${LLVM_DEFINITIONS_LIST})
target_link_libraries(generate_cpp_ir_generator PRIVATE LLVM)

set(IR_GENERATOR_SOURCE
        "${CMAKE_CURRENT_SOURCE_DIR}/assignments/03-ir-generator/app/ir_generator.cpp")

add_custom_command(
        OUTPUT "${IR_GENERATOR_SOURCE}"
        COMMAND generate_cpp_ir_generator
                "${CMAKE_CURRENT_SOURCE_DIR}/assignments/01-graphics/app.ll"
                "${IR_GENERATOR_SOURCE}"
        DEPENDS generate_cpp_ir_generator
                "${CMAKE_CURRENT_SOURCE_DIR}/assignments/01-graphics/app.ll"
        VERBATIM)

add_custom_target(generate_ir_generator
        DEPENDS "${IR_GENERATOR_SOURCE}")

# IR generation and execution
add_executable(generate_ir
        assignments/03-ir-generator/app/generate_ir.cpp
        "${IR_GENERATOR_SOURCE}"
        lib/sim/sim.c)

add_dependencies(generate_ir generate_ir_generator)

target_include_directories(generate_ir SYSTEM PRIVATE ${LLVM_INCLUDE_DIRS})
target_include_directories(generate_ir PRIVATE lib/sim)
target_compile_options(generate_ir PRIVATE ${LLVM_DEFINITIONS_LIST})
target_link_libraries(generate_ir PRIVATE LLVM PkgConfig::SDL2)

add_custom_target(run_ir_generator
        COMMAND $<TARGET_FILE:generate_ir>
        USES_TERMINAL
        VERBATIM)
