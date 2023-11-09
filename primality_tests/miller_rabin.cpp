#include "primality_tests.hpp"

#include <chrono>
#include <random>

namespace primality_tests {

namespace {

uint64_t binpower(uint64_t base, uint64_t e, uint64_t mod);
bool check_strong_liar(uint64_t n, uint64_t a, uint64_t d, int s);
uint64_t rand_range(uint64_t low, uint64_t high);

} // namespace

bool miller_rabin(uint64_t n, int k) {
    if (n < 4) {
        return n == 2 || n == 3;
    }

    int s = 0;
    uint64_t d = n - 1;
    while (d % 2 == 0) {
        d /= 2;
        s++;
    }

    for (int _ = 0; _ < k; _++) {
        uint64_t a = rand_range(2, n - 2);
        if (check_strong_liar(n, a, d, s)) {
            return false;
        }
    }
    return true;
}

namespace {

bool check_strong_liar(uint64_t n, uint64_t a, uint64_t d, int s) {
    uint64_t x = binpower(a, d, n);
    if (x == 1 || x == n - 1)
        return false;
    for (int r = 1; r < s; r++) {
        x = (__uint128_t)x * x % n;
        if (x == n - 1)
            return false;
    }
    return true;
}

uint64_t binpower(uint64_t base, uint64_t e, uint64_t mod) {
    uint64_t result = 1;
    base %= mod;

    while (e > 0) {
        if (e % 2 == 1) {
            result = (__uint128_t)result * base % mod;
        }

        base = (__uint128_t)base * base % mod;
        e >>= 1;
    }

    return result;
}

uint64_t rand_range(uint64_t low, uint64_t high) {
    static std::mt19937_64 gen(std::chrono::steady_clock::now().time_since_epoch().count());
    std::uniform_int_distribution<uint64_t> dist(low, high);
    return dist(gen);
}

} // namespace

} // namespace primality_tests
