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
