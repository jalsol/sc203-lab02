#include "prime_sieving.hpp"

#include "../primality_tests/primality_tests.hpp"

namespace prime_sieving {

std::vector<uint64_t> primality_test(uint64_t n) {
    std::vector<uint64_t> result;

    for (uint64_t i = 2; i <= n; ++i) {
        if (primality_tests::miller_rabin(n)) {
            result.push_back(i);
        }
    }

    return result;
}

} // namespace prime_sieving
