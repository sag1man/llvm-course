# Runtime IR Usage Analysis

The LLVM pass instruments `app.c` module after `-O2` optimization. 
Before each non-PHI user instruction, it inserts one `trace_use` call per instruction-valued operand. 

The runtime analyzer counts windows of 1–5 `User <- Operand` opcode pairs. 
It stores frequencies and the last five events, without saving the raw trace.

## Stats

Collection stopped after **1,000,000,000 events**. 
Measured wall time was **58.013 seconds**.

| Window size | Total windows | Unique patterns |
|-------------|--------------:|----------------:|
| 1           | 1,000,000,000 |              38 |
| 2           |   999,999,999 |              68 |
| 3           |   999,999,998 |              90 |
| 4           |   999,999,997 |             108 |
| 5           |   999,999,996 |             123 |

### Window of size 1

The most frequent pair is `mul <- sub` (**135,827,440 occurrences**), 
corresponding to squaring coordinate differences in the distance calculation.

### Window of size 5

Longer patterns are dominated by array addressing, loads, and coordinate subtraction. 
The most frequent five-event pattern is:

```
getelementptr <- alloca | getelementptr <- phi | load <- getelementptr | sub <- phi | sub <- load
```

It occurs **67,913,720 times**.

Full statistics: [patterns.txt](results/patterns.txt).

## Commands used

From the repository root:

```bash
cmake --build cmake-build-debug --target TraceUses trace_runtime -j 4

clang-18 -O2 \
  -fpass-plugin=./cmake-build-debug/TraceUses.so \
  -Ilib/sim \
  -S -emit-llvm assignments/01-graphics/app.c \
  -o build/app.instrumented.ll

opt-18 -passes=verify -disable-output build/app.instrumented.ll

clang-18 -O0 -c build/app.instrumented.ll -o build/app.instrumented.o

clang-18 -O2 -Ilib/sim $(sdl2-config --cflags) \
  -c lib/sim/sim.c -o build/sim.o

clang-18 -O2 -Ilib/sim \
  -c lib/sim/start.c -o build/start.o

clang++-18 \
  build/start.o build/sim.o build/app.instrumented.o \
  cmake-build-debug/libtrace_runtime.a \
  $(sdl2-config --libs) \
  $(llvm-config-18 --ldflags --link-shared --libs core --system-libs) \
  -o build/app-traced

time ./build/app-traced > assignments/02-pass/results/patterns.txt
```