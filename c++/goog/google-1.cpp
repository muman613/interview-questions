// C++ Assessment - Google Job Posting ID: G-REQ-166473 - Michael Uman
// Q: Please write a C++ code to remove duplicates from an array of numbers while preserving order. State your assumptions in bullet point.

#include <iostream>
#include <map>
#include <vector>

using namespace std;

typedef vector<int>             int_vector;
typedef map<int, int>           int_map;


/**
 * Return a copy of the array with only the unique values in original order.
 *
 * @param input
 * @param output
 * @return
 */
bool get_ordered_array(const int_vector &input, int_vector &output) {
    int_map m;

    for (auto const & n : input) {
        m[n]++;
        if (m[n] == 1)
            output.push_back(n);
    }

    return (!output.empty());
}

/**
 * Remove duplicates from array.
 *
 * @param i
 * @return
 */

bool remove_duplicates(int_vector & i) {
    int_map m;

    for (auto it = i.begin() ; it != i.end() ; it++) {
        int n = *it;
        m[n]++;
        if (m[n] > 1) {
            i.erase(it);
        }
    }

    return (!i.empty());
}

int main() {
    int_vector input_array = {
            2,
            10,
            4,
            6,
            10,
            2,
            17,
            17,
            4,
            22
    };
    int_vector output_array;

    if (get_ordered_array(input_array, output_array)) {
        for (auto n : output_array) {
            cout << n << "\n";
        }
    }

    remove_duplicates(input_array);

    return 0;
}


