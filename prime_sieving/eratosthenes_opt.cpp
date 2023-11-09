#include "prime_sieving.hpp"

#include <cmath>
#include <algorithm>

namespace prime_sieving {

namespace {

uint64_t iceil(uint64_t a, uint64_t b) {
    return (a + b - 1) / b;
}

} // namespace

std::vector<uint64_t> segmented_sieve(uint64_t n) {
    constexpr uint64_t S = 10000;
    std::vector<uint64_t> small_primes = sieve_of_eratosthenes(std::sqrt(n));
    std::vector<uint64_t> result;
    std::vector<char> marked(S);

    for (uint64_t k = 0; k * S <= n; k++) {
        std::fill(marked.begin(), marked.end(), false);
        uint64_t start = k * S;

        for (uint64_t p : small_primes) {
            uint64_t mul = std::max(p * p, iceil(start, p) * p);

            for (; mul - start < S; mul += p) {
                marked[mul - start] = true;
            }
        }

        if (k == 0) {
            marked[0] = marked[1] = true;
        }

        for (uint64_t i = 0; i < S && start + i <= n; i++) {
            if (!marked[i]) {
                result.push_back(i + start);
            }
        }
    }

    return result;
}

} // namespace prime_sieving
