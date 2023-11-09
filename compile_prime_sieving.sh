#!/bin/bash
g++ -o benchmark_prime_sieving benchmark_prime_sieving.cpp prime_sieving/*.cpp primality_tests/miller_rabin.cpp -O2 -Wall -Wextra -march=native

