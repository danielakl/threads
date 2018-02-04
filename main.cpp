#include "prime.hpp"
#include <iostream>
#include <regex>
#include <thread>


using namespace std;

int main() {
    unsigned numThreads = thread::hardware_concurrency();
    set<unsigned> primes;
    vector<thread> threads;
    mutex numMutex;

    // Get interval from user.
    string input;
    cout << "Enter a range to find prime numbers within: ";
    getline(cin, input);

    // Extract numbers.
    regex regex("[0-9]+");
    sregex_iterator iterator(input.begin(), input.end(), regex);
    sregex_iterator itEnd;
    unsigned values[2] = {0, 0};
    for (unsigned &value : values) {
        if (iterator != itEnd) {
            value = unsigned(stoi((*iterator)[0]));
            ++iterator;
        }
    }

    // Find min and max value.
    unsigned min = values[0];
    unsigned max = values[1];
    if (max < min) {
        unsigned temp = max;
        max = min;
        min = temp;
    }
    int delta = max - min;

    // Find prime numbers.
    cout << "Running on " << numThreads << " thread" << ((numThreads == 1) ? "." : "s.") << endl;
    if (numThreads == 0) {
        findPrimes(min, max, primes, numMutex);
    } else {
        for (size_t i = 0; i < numThreads; i++) {
            unsigned start = min + (i * delta / numThreads);
            unsigned end = min + ((i + 1) * delta / numThreads);
            threads.emplace_back(thread(findPrimes, start, end, ref(primes), ref(numMutex)));
        }
    }

    // Wait for all threads to finish.
    for (auto &thread : threads) {
        thread.join();
    }

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
