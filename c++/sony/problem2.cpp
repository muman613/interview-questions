#include <iostream>
#include <cstring>

using namespace std;

const int bm_width = 8;
const int bm_height = 8;


int bm_data[64] = {
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 1, 0, 1, 1,
        0, 1, 1, 0, 0, 0, 1, 1,
        0, 1, 1, 0, 1, 1, 0, 0,
        0, 0, 0, 0, 1, 1, 0, 0,
        1, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 1, 1, 0, 0, 0, 0,
        0, 0, 1, 1, 0, 0, 0, 1,
};

#define GET_BIT(DATA,X,Y) DATA[((Y) * bm_width) + (X)]
#define SET_BIT(DATA,X,Y,B) DATA[((Y) * bm_width) + (x)] = B

/**
 * Test for the 2x2 square of 1 bits.
 * @param bm Pointer to bitmap storage
 * @param x X offset
 * @param y Y offset
 * @return return true if there is a 2x2 square of 1 bits at this offset
 */
bool check_square_2x2(int * bm, int x, int y) {
    bool res = false;

    if ((GET_BIT(bm, x, y) == 1) &&
        (GET_BIT(bm, x+1, y) == 1) &&
        (GET_BIT(bm, x, y+1) == 1) &&
        (GET_BIT(bm, x+1, y+1) == 1))
    {
        // We must set the discovered bits to zero so that we don't mistakenly discover
        // another 2x2 rectangle just because the next line contains 1 bits at this horizontal
        // location.

        SET_BIT(bm, x, y, 0);
        SET_BIT(bm, x+1, y, 0);
        SET_BIT(bm, x, y+1, 0);
        SET_BIT(bm, x+1, y+1, 0);

        res = true;
    }

    return res;
}

/**
 * Analyze the bitmap looking for 2x2 patterns of 1 bits.
 *
 * @param bm
 * @param width
 * @param height
 * @return # of 2x2 bitmaps found.
 */
int analyze_bitmap(int * bm, int width, int height) {
    auto * bm_copy = (int *)malloc(width * height * sizeof(int));
    if (bm_copy == nullptr) {
        cerr << "ERROR: Failed to allocate copy." << endl;
        return -1;
    }
    memcpy(bm_copy, bm, width * height * sizeof(int));

    int cnt = 0;
    for (int y = 0; y < (height - 1); y++) {
        for (int x = 0; x < (width - 1); x++) {
            if (check_square_2x2(bm_copy, x, y)) {
                cnt++;
            }
        }
    }

    free((void*)bm_copy);

    return cnt;
}


int main() {
    int cnt = analyze_bitmap(bm_data, bm_width, bm_height);

    cout << "Analysis found " << cnt << " 2x2 squares of 1 bits in bitmap...\n";

    return 0;
}