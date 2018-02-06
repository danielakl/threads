#include "prime.hpp"
#include <iostream>
#include <regex>
#include <thread>


using namespace std;

typedef unsigned long long int ulli;

int main() {
    ulli numThreads = thread::hardware_concurrency();
    set<ulli> primes;
    vector <thread> threads;
    mutex numMutex;

    // Get interval from user.
    string input;
    cout << "Enter a range to find prime numbers within: ";
    getline(cin, input);

    // Extract numbers.
    regex regex("[0-9]+");
    sregex_iterator iterator(input.begin(), input.end(), regex);
    sregex_iterator itEnd;
    ulli values[2] = {0, 0};
    for (ulli &value : values) {
        if (iterator != itEnd) {
            value = stoll((*iterator)[0]);
            ++iterator;
        }
    }

    // Find min and max value.
    ulli min = values[0];
    ulli max = values[1];
    if (max < min) {
        ulli temp = max;
        max = min;
        min = temp;
    }
    ulli delta = max - min;

#pragma omp parallel for
    for (ulli j = min; j < max; ++j) {
        if (isPrime(j)) {
            lock_guard <mutex> lock(numMutex);
            primes.insert(j);
        }
    }

//    // Find prime numbers.
//    cout << "Running on " << numThreads << " thread" << ((numThreads == 1) ? "." : "s.") << endl;
//    if (numThreads == 0) {
//        findPrimes(min, max, primes, numMutex);
//    } else {
//        for (size_t i = 0; i < numThreads; i++) {
//            ulli start = min + (i * delta / numThreads);
//            ulli end = min + ((i + 1) * delta / numThreads);
//            threads.emplace_back(thread(findPrimes, start, end, ref(primes), ref(numMutex)));
//        }
//    }
//
//    // Wait for all threads to finish.
//    for (auto &thread : threads) {
//        thread.join();
//    }

    // Print primes
    for (auto it = primes.cbegin(); it != primes.cend(); ++it) {
        cout << *it;
        if (it != --primes.cend()) {
            cout << " | ";
        } else {
            cout << endl;
        }
    }

    return 0;
}
