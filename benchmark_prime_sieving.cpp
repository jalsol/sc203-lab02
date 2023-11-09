#include "prime_sieving/prime_sieving.hpp"

#include <iostream>
#include <chrono>

// time limit is 10 seconds
// above 10 seconds -> N/A next turn
constexpr long double time_limit = 10000;

int main() {
    bool run_primality_test = true;
    bool run_eratosthenes = true;
    bool run_eratosthenes_opt = true;

    uint64_t n = 10000;
    for (int i = 4; i <= 10; i++, n *= 10) {
        std::cout << "Sieving primes up to " << n << std::endl;

        uint64_t tot_primality = 0;
        uint64_t tot_eratosthenes = 0;
        uint64_t tot_eratosthenes_opt = 0;

        if (run_primality_test) {
            auto start = std::chrono::high_resolution_clock::now();
            auto primes = prime_sieving::primality_test(n);
            auto end = std::chrono::high_resolution_clock::now();

            tot_primality += std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
        }

        if (run_eratosthenes) {
            auto start = std::chrono::high_resolution_clock::now();
            auto primes = prime_sieving::sieve_of_eratosthenes(n);
            auto end = std::chrono::high_resolution_clock::now();

            tot_eratosthenes += std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
        }

        if (run_eratosthenes_opt) {
            auto start = std::chrono::high_resolution_clock::now();
            auto primes = prime_sieving::segmented_sieve(n);
            auto end = std::chrono::high_resolution_clock::now();

            tot_eratosthenes_opt += std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
        }

        if (run_primality_test) {
            std::cout << "Primality test: " << tot_primality << " ms" << std::endl;
        } else {
            std::cout << "Primality test: N/A" << std::endl;
        }

        if (run_eratosthenes) {
            std::cout << "Sieve of Eratosthenes: " << tot_eratosthenes << " ms" << std::endl;
        } else {
            std::cout << "Sieve of Eratosthenes: N/A" << std::endl;
        }

        if (run_eratosthenes_opt) {
            std::cout << "Segmented sieve of Eratosthenes: " << tot_eratosthenes_opt << " ms" << std::endl;
        } else {
            std::cout << "Segmented sieve of Eratosthenes: N/A" << std::endl;
        }

        if (run_primality_test && tot_primality > time_limit) {
            run_primality_test = false;
        }

        if (run_eratosthenes && tot_eratosthenes > time_limit) {
            run_eratosthenes = false;
        }

        if (run_eratosthenes_opt && tot_eratosthenes_opt > time_limit) {
            run_eratosthenes_opt = false;
        }

        std::cout << "==========================================" << std::endl;
    }
}
