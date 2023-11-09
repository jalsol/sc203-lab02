#include "prime_sieving.hpp"

namespace prime_sieving {

std::vector<uint64_t> sieve_of_eratosthenes(uint64_t n) {
    std::vector<uint64_t> result;

    std::vector<bool> marked(n + 1, false);
    marked[0] = marked[1] = true;

    for (uint64_t i = 2; i * i <= n; i++) {
        if (!marked[i]) {
            for (uint64_t j = i * i; j <= n; j += i) {
                marked[j] = true;
            }
        }
    }

    for (uint64_t i = 2; i <= n; i++) {
        if (!marked[i]) {
            result.push_back(i);
        }
    }

    return result;
}

} // namespace prime_sieving
