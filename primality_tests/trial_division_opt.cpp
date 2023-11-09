#include "primality_tests.hpp"

namespace primality_tests {

bool trial_division_opt(uint64_t n) {
    if (n <= 1) {
        return false;
    }

    for (uint64_t i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            return false;
        }
    }

    return true;
}

} // namespace primality_tests
