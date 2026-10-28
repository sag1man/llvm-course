# LLVM IR Generator

- `Llvm2CppIrGenerator` converts [app.ll](../01-graphics/app.ll) into
  [C++ source](app/ir_generator.cpp) that reconstructs the module using the LLVM API.
- The generated program verifies and prints the IR, then executes `app`
- `simPutPixel`, `simFlush`, and `simRand` are mapped to native functions from `lib/sim`.

## Commands

From the repository root:

```bash
# Generate app/ir_generator.cpp
cmake --build cmake-build-debug --target generate_ir_generator -j 4

# Generate, build, and run the application
cmake --build cmake-build-debug --target run_ir_generator -j 4
```
