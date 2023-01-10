#pragma once
#include <cstdint>

enum e_flag : size_t {
  eq = 0u, // equal
  lt,      // less than
  gt,      // greater than
  FLAGS_END
};