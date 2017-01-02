#include <iostream>
#include <math.h>

void generate_sieve(unsigned sieve_size) {
    // Init
    bool *is_prime = new bool[sieve_size + 1];
    for (unsigned i = 2; i <= sieve_size; ++i) {
        is_prime[i] = true;
    }

    // Generate sieve
    for (unsigned i = 2; i <= sqrt(sieve_size); ++i) {
        if (is_prime[i]) {
            for (int j = i * i; j <= sieve_size; j += i) {
                is_prime[j] = false;
            }
        }
    }

    // Output primes
    std::cout << "Prime numbers to " << sieve_size << std::endl;
    for (unsigned i = 2; i < sieve_size; ++i) {
        if (is_prime[i]) {
            std::cout << i << std::endl;
        }
    }

    delete[] is_prime;
}

int main() {
    unsigned sieve_size;
    std::cout << "Sieve size: ";
    std::cin >> sieve_size;
    generate_sieve(sieve_size);
    return 0;
}
