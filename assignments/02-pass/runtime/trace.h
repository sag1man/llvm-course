// trace.h

#pragma once

#include <stdint.h> // NOLINT(*-deprecated-headers)

#ifdef __cplusplus
extern "C" {
#endif

void trace_use(uint32_t user_opcode, uint32_t operand_opcode);
void trace_finish(void);

#ifdef __cplusplus
}
#endif
