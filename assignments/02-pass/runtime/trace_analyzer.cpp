#include "trace_analyzer.h"

#include "llvm/IR/Instruction.h"

#include <algorithm>
#include <functional>
#include <iostream>
#include <utility>
#include <vector>

std::size_t TraceAnalyzer::PatternHash::operator()(const Pattern& pattern) const noexcept {
  std::size_t hash = 0;
  for (const Event event : pattern) {
    constexpr std::size_t HASH = 0x9e3779b9u;
    hash ^= std::hash<Event>{}(event) + HASH + (hash << 6u) + (hash >> 2u); // NOLINT(*-magic-numbers)
  }
  return hash;
}

void TraceAnalyzer::record(const std::uint32_t user_opcode, const std::uint32_t operand_opcode) {
  const Event key = (static_cast<Event>(user_opcode) << 32u) | static_cast<Event>(operand_opcode);

  if (history_size == MAX_WINDOW) {
    for (std::size_t i = 1; i < MAX_WINDOW; ++i) {
      history.at(i - 1) = history.at(i);
    }
    --history_size;
  }

  history.at(history_size++) = key;

  for (std::size_t length = 1; length <= history_size; ++length) {
    Pattern pattern{};

    for (std::size_t i = 0; i < length; ++i) {
      pattern.at(i) = history.at(history_size - length + i);
    }

    ++counts.at(length - 1)[pattern];
  }
}

void TraceAnalyzer::print_statistics() const {
  for (std::size_t length = 1; length <= MAX_WINDOW; ++length) {
    const auto& table = counts.at(length - 1);

    std::vector<std::pair<Pattern, std::uint64_t>> sorted_counts(table.begin(), table.end());

    std::sort(sorted_counts.begin(), sorted_counts.end(), [](const auto& left, const auto& right) {
      if (left.second != right.second) {
        return left.second > right.second;
      }
      return left.first < right.first;
    });

    std::cout << "Window " << length << ":\n";

    for (const auto& [pattern, count] : sorted_counts) {
      for (std::size_t i = 0; i < length; ++i) {
        if (i != 0) {
          std::cout << " | ";
        }

        const auto user_opcode = static_cast<std::uint32_t>(pattern.at(i) >> 32u);
        const auto operand_opcode = static_cast<std::uint32_t>(pattern.at(i));

        std::cout << llvm::Instruction::getOpcodeName(user_opcode) << " <- "
                  << llvm::Instruction::getOpcodeName(operand_opcode);
      }

      std::cout << ": " << count << '\n';
    }

    std::cout << '\n';
  }
}
