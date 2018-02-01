#include <iostream>
#include <regex>
#include <thread>
#include <cmath>
#include <mutex>

using namespace std;

unsigned numThreads = thread::hardware_concurrency();
vector<unsigned> primes;
vector<thread> threads;
mutex numMutex;

bool isPrime(const unsigned number) {
    if (number < 2) return false;
    for (unsigned i = 2; i < number; i++) {
        if (number % i == 0) {
            return false;
        }
    }
    return true;
}

void findPrimes(const unsigned start, const unsigned end) {
    std::thread::id this_id = std::this_thread::get_id();
    for (unsigned i = start; i <= end; i++) {
        if (isPrime(i)) {
            lock_guard<mutex> lock(numMutex);
            primes.push_back(i);
        }
    }
}

int main() {
    //while (true) {
    // Get interval from user.
    string input;
    cout << "Enter a range to find prime numbers within: ";
    getline(cin, input);

    // Extract numbers.
    regex regex("[0-9]+");
    sregex_iterator iterator(input.begin(), input.end(), regex);
    sregex_iterator itEnd;
    unsigned values[2];
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
    for (size_t i = 0; i < numThreads; i++) {
        auto start = unsigned(ceil(min + (i * (delta / numThreads))));
        auto end = unsigned(floor(min + ((i + 1) * (delta / numThreads))));
        threads.emplace_back(thread(findPrimes, start, end));
    }

    // Wait for all threads to finish.
    for (auto &thread : threads) {
        thread.join();
    }

    // Sort prime table.
    sort (primes.begin(), primes.end());

    // Print primes
    for (auto i = primes.begin(); i != primes.end(); ++i) {
        if (i != primes.end()-1) {
            cout << *i << " | ";
        } else {
            cout << *i << endl;
        }
    }

    //}
    return 0;
}