#include "prime.hpp"
#include <cassert>
#include <vector>
#include <algorithm>

using namespace std;
typedef unsigned long long int ulli;

int main() {
    const vector<ulli> primes = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};
    const vector<ulli> nonPrimes = {0, 1, 4, 6, 8, 9, 10, 12, 14, 15, 16,
                                        18, 20, 21, 22, 24, 25, 26, 27, 28, 30};

    for (const ulli prime : primes) {
        assert(isPrime(prime));
    }

    for (const ulli nonPrime : nonPrimes) {
        assert(!isPrime(nonPrime));
    }

    std::mutex numMutex;
    std::set<ulli> foundPrimes;
    findPrimes(0, 30, foundPrimes, numMutex);
    for (const ulli found : foundPrimes) {
        assert(find(primes.begin(), primes.end(), found) != primes.end());
        assert(find(nonPrimes.begin(), nonPrimes.end(), found) == nonPrimes.end());
    }
}