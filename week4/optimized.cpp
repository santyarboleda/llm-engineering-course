#include <iostream>
#include <vector>
#include <limits>
#include <chrono>

using namespace std;

// Linear congruential generator
class LCG {
public:
    LCG(uint32_t seed, uint32_t a = 1664525, uint32_t c = 1013904223, uint32_t m = 1U << 32)
        : value(seed), a(a), c(c), m(m) {}

    uint32_t next() {
        value = (a * value + c) % m;
        return value;
    }
    
private:
    uint32_t value, a, c, m;
};

// Maximum subarray sum using Kadane's algorithm for efficiency
int64_t max_subarray_sum(int n, uint32_t seed, int min_val, int max_val) {
    LCG lcg(seed);
    vector<int> random_numbers(n);
    for (int i = 0; i < n; ++i) {
        random_numbers[i] = (lcg.next() % (max_val - min_val + 1)) + min_val;
    }

    int64_t current_sum = 0, max_sum = numeric_limits<int64_t>::min();
    for (int i = 0; i < n; ++i) {
        current_sum += random_numbers[i];
        if (current_sum > max_sum) max_sum = current_sum;
        if (current_sum < 0) current_sum = 0;
    }
    return max_sum;
}

// Total maximum subarray sum over 20 iterations
int64_t total_max_subarray_sum(int n, uint32_t initial_seed, int min_val, int max_val) {
    int64_t total_sum = 0;
    LCG lcg(initial_seed);
    for (int i = 0; i < 20; ++i) {
        uint32_t seed = lcg.next();
        total_sum += max_subarray_sum(n, seed, min_val, max_val);
    }
    return total_sum;
}

int main() {
    int n = 10000;
    uint32_t initial_seed = 42;
    int min_val = -10;
    int max_val = 10;

    auto start_time = chrono::high_resolution_clock::now();
    int64_t result = total_max_subarray_sum(n, initial_seed, min_val, max_val);
    auto end_time = chrono::high_resolution_clock::now();
    chrono::duration<double> execution_time = end_time - start_time;

    cout << "Total Maximum Subarray Sum (20 runs): " << result << endl;
    cout << "Execution Time: " << execution_time.count() << " seconds" << endl;

    return 0;
}
