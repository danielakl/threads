#include "prime.hpp"
#include <cassert>
#include <algorithm>

using namespace std;

int main() {
    const vector<unsigned> primes = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};
    const vector<unsigned> nonPrimes = {0, 1, 4, 6, 8, 9, 10, 12, 14, 15, 16,
                                        18, 20, 21, 22, 24, 25, 26, 27, 28, 30};

    for (unsigned prime : primes) {
        assert(isPrime(prime));
    }

    for (unsigned nonPrime : nonPrimes) {
        assert(!isPrime(nonPrime));
    }

    std::mutex numMutex;
    std::vector<unsigned> foundPrimes;
    findPrimes(0, 30, foundPrimes, numMutex);
    for (unsigned found : foundPrimes) {
        assert(find(primes.begin(), primes.end(), found) != primes.end());
        assert(find(nonPrimes.begin(), nonPrimes.end(), found) == nonPrimes.end());
    }
}