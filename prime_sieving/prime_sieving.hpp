#pragma once

#include <vector>
#include <cstdint>

namespace prime_sieving {

std::vector<uint64_t> primality_test(uint64_t n);
std::vector<uint64_t> sieve_of_eratosthenes(uint64_t n);
std::vector<uint64_t> segmented_sieve(uint64_t n);

} // namespace prime_sieving
