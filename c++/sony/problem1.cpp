#include <iostream>

using namespace std;

int original_loop() {
    int res = 0;

    for (int i = 1 ; i < 100 ; i++) {
        if (((i % 3) == 0) && ((i % 5) == 0)) {
            cout << "PR\n";
        } else if ((i % 3) == 0) {
            cout << "P\n";
        } else if ((i % 5) == 0) {
            cout << "R\n";
        } else {
            cout << i << '\n';
        }
    }

    return res;
}

/**
 * Optimized loop - Using lookup table for output.
 *
 * @return
 */
int optimized_loop() {
    int res = 0;
    static const char * displayText[] = {
            nullptr,
            "R",
            "P",
            "PR"
    };

    for (int i = 1 ; i < 100 ; i++) {
        int nMod3 = ((i % 3) == 0)?1:0;
        int nMod5 = ((i % 5) == 0)?1:0;

        if (nMod3 || nMod5) {
            cout << displayText[(nMod3 << 1) + nMod5] << '\n';
        } else {
            cout << i << '\n';
        }
    }

    return res;
}

int main() {
    std::cout << "Hello, Sony!" << std::endl;

    original_loop();

    cout << "---------------------------------" << endl;

    optimized_loop();

    return 0;
}