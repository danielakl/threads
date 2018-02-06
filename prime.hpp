#include <mutex>
#include <set>
#include <cmath>

using namespace std;

typedef unsigned long long int ulli;

bool isPrime(const ulli number) {
    if (number < 2) return false;
    if (number == 2) return true;
    if (number % 2 == 0) return false;
    ulli max = sqrt(number);
    for (ulli i = 3; i <= max; i += 2) {
        if (number % i == 0) {
            return false;
        }
    }
    return true;
}

void findPrimes(const ulli start, const ulli end, const ulli jump, set<ulli> &primes, mutex &numMutex) {
    for (ulli i = start; i <= end; i += jump) {
        if (isPrime(i)) {
            lock_guard<mutex> lock(numMutex);
            primes.insert(i);
        }
    }
}