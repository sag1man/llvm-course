// trace.cpp

#include "trace.h"

#include "trace_analyzer.h"

#include <cstdlib>

namespace {

TraceAnalyzer& analyzer() {
  static TraceAnalyzer instance;
  return instance;
}

} // namespace

void trace_use(const uint32_t user_opcode, const uint32_t operand_opcode) {
  static constexpr uint64_t EVENT_LIMIT = 1'000'000'000;
  static uint64_t event_count = 0;

  analyzer().record(user_opcode, operand_opcode);

  if (++event_count == EVENT_LIMIT) {
    trace_finish();
    std::exit(EXIT_SUCCESS); // NOLINT(*-mt-unsafe)
  }
}

void trace_finish(void) {
  analyzer().print_statistics();
}
