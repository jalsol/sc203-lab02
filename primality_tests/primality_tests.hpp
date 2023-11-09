#pragma once

#include <cstdint>

namespace primality_tests {

bool trial_division(uint64_t n);
bool trial_division_opt(uint64_t n);
bool miller_rabin(uint64_t n, int k = 5);

} // namespace primality_tests
