#include <mutex>
#include <set>

using namespace std;

bool isPrime(const unsigned number) {
    if (number < 2) return false;
    for (unsigned i = 2; i < number; i++) {
        if (number % i == 0) {
            return false;
        }
    }
    return true;
}

void findPrimes(const unsigned start, const unsigned end, set<unsigned> &primes, mutex &numMutex) {
    for (unsigned i = start; i <= end; i++) {
        if (isPrime(i)) {
            lock_guard<mutex> lock(numMutex);
            primes.insert(i);
        }
    }
}