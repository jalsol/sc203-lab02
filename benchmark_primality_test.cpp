#include "primality_tests/primality_tests.hpp"

#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>


// time limit is 10 seconds
// above 10 seconds -> N/A next turn
constexpr long double time_limit = 10000;
constexpr int start_size = 8;
constexpr int end_size = 64;
constexpr int step_size = 4;
constexpr int num_primes = 67;

int main() {
    system("python3 gen_primes.py > primes.txt");
    std::ifstream fin("primes.txt");

    bool run_trial_division = true;
    bool run_trial_division_opt = true;
    bool run_miller_rabin = true;

    for (int size = start_size; size <= end_size; size += step_size) {
        std::vector<uint64_t> primes(num_primes);
        for (auto& p : primes) fin >> p;

        std::cout << "Testing primes of size " << size << " bits" << std::endl;

        uint64_t tot_trial = 0;
        uint64_t tot_trial_opt = 0;
        uint64_t tot_miller_rabin = 0;

        for (auto p : primes) {
            if (run_trial_division) {
                auto start = std::chrono::high_resolution_clock::now();
                bool is_prime = primality_tests::trial_division(p);
                auto end = std::chrono::high_resolution_clock::now();

                tot_trial += std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
                if (!is_prime) {
                    std::cerr << "Trial division failed on " << p << std::endl;
                    std::exit(1);
                }
            }

            if (run_trial_division_opt) {
                auto start = std::chrono::high_resolution_clock::now();
                bool is_prime = primality_tests::trial_division_opt(p);
                auto end = std::chrono::high_resolution_clock::now();

                tot_trial_opt += std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
                if (!is_prime) {
                    std::cerr << "Trial division opt failed on " << p << std::endl;
                    std::exit(1);
                }
            }

            if (run_miller_rabin) {
                auto start = std::chrono::high_resolution_clock::now();
                bool is_prime = primality_tests::miller_rabin(p);
                auto end = std::chrono::high_resolution_clock::now();

                tot_miller_rabin += std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
                if (!is_prime) {
                    std::cerr << "Miller-Rabin failed on " << p << std::endl;
                    std::exit(1);
                }
            }
        }

        long double avg_trial = tot_trial / 10.0;
        long double avg_trial_opt = tot_trial_opt / 10.0;
        long double avg_miller_rabin = tot_miller_rabin / 10.0;

        if (run_trial_division) {
            std::cout << "Trial division: " << avg_trial << " ms" << std::endl;
        } else {
            std::cout << "Trial division: N/A" << std::endl;
        }

        if (run_trial_division_opt) {
            std::cout << "Trial division opt: " << avg_trial_opt << " ms" << std::endl;
        } else {
            std::cout << "Trial division opt: N/A" << std::endl;
        }

        if (run_miller_rabin) {
            std::cout << "Miller-Rabin: " << avg_miller_rabin << " ms" << std::endl;
        } else {
            std::cout << "Miller-Rabin: N/A" << std::endl;
        }

        if (run_trial_division && avg_trial > time_limit) {
            run_trial_division = false;
        }

        if (run_trial_division_opt && avg_trial_opt > time_limit) {
            run_trial_division_opt = false;
        }

        if (run_miller_rabin && avg_miller_rabin > time_limit) {
            run_miller_rabin = false;
        }

        std::cout << "==========================================" << std::endl;
    }
}
