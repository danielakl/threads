#include <mutex>
#include <vector>

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

void findPrimes(const unsigned start, const unsigned end, vector<unsigned> &primes, mutex &numMutex) {
//    std::thread::id this_id = std::this_thread::get_id(); // TODO: Remove this?
    for (unsigned i = start; i <= end; i++) {
        if (isPrime(i)) {
            lock_guard<mutex> lock(numMutex);
            primes.push_back(i);
        }
    }
}