#include <iostream>
#include <regex>
#include <thread>
#include <cmath>
#include <mutex>

using namespace std;

unsigned numThreads = thread::hardware_concurrency();

bool isPrime(const unsigned number) {
    for (size_t i = 3; i < number; i++) {
        if (number % i == 0) {
            return false;
        }
    }
    return true;
}

void findPrimes(const unsigned start, const unsigned end, vector<unsigned> &primes) {
    for (unsigned i = start; i <= end; i++) {
        if (isPrime(i)) {
            primes.push_back(i);
        }
    }
}

int main() {
    //while (true) {
    // Get interval from user.
    string input;
    cout << "[DEBUG] Number of Threads: " << numThreads << endl;
    cout << "Enter a range to find prime numbers within: ";
    getline(cin, input);
    cout << "[DEBUG] Line: " << input << endl;

    // Extract numbers.
    regex regex("[0-9]+");
    sregex_iterator iterator(input.begin(), input.end(), regex);
    sregex_iterator itEnd;
    unsigned values[2];
    for (unsigned int &value : values) {
        if (iterator != itEnd) {
            cout << "[DEBUG] Match: " << (*iterator)[0] << endl;
            value = stoi((*iterator)[0]);
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
    cout << "[DEBUG] min: " << min << endl;
    cout << "[DEBUG] max: " << max << endl;
    int delta = max - min;

    // Find prime numbers.
    vector<unsigned> primes;
    vector<thread> threads;
    mutex numMutex;
    for (size_t i = 0; i < numThreads; i++) {
        auto start = unsigned(ceil(min + (i * (delta / numThreads))));
        auto end = unsigned(floor(min + (i + 1 * (delta / numThreads))));
        //threads.emplace_back(thread(findPrimes, start, end, primes));
        threads.emplace_back([start, end, &primes, &numMutex] {
            for (unsigned j = start; j <= end; j++) {
                if (isPrime(j)) {
                    cout <<  j << ", ";
                    lock_guard<mutex> lock(numMutex);
                    primes.push_back(j);
                }
            }
        });
    }

    // Wait for all threads to finish.
    for (auto &thread : threads) {
        thread.join();
    }

    // Sort prime table.

    // Print primes
    //for (auto &prime : primes) {
    //    cout << prime << ", ";
    //}
    cout << endl;

    //}
    return 0;
}