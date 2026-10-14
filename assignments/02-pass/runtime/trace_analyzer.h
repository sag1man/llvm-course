// trace_analyzer.h

#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include <unordered_map>

class TraceAnalyzer {
public:
  void record(std::uint32_t user_opcode, std::uint32_t operand_opcode);
  void print_statistics() const;

private:
  static constexpr std::size_t MAX_WINDOW = 5;

  using Event = std::uint64_t;
  using Pattern = std::array<Event, MAX_WINDOW>;

  struct PatternHash {
    std::size_t operator()(const Pattern& pattern) const noexcept;
  };

  using Counts = std::unordered_map<Pattern, std::uint64_t, PatternHash>;

  std::array<Counts, MAX_WINDOW> counts{};
  std::array<Event, MAX_WINDOW> history{};
  std::size_t history_size = 0;
};
