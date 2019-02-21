#include <iostream>
#include <cstring>
#include <fstream>
#include <vector>
#include <algorithm>


using namespace std;


// trim from start (in place)
static inline void ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch) {
        return !std::isspace(ch);
    }));
}

// trim from end (in place)
static inline void rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) {
        return !std::isspace(ch);
    }).base(), s.end());
}

// trim from both ends (in place)
static inline void trim(std::string &s) {
    ltrim(s);
    rtrim(s);
}

// for string delimiter
vector<string> split (const string &s, const string &delimiter) {
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    string token;
    vector<string> res;

    while ((pos_end = s.find (delimiter, pos_start)) != string::npos) {
        token = s.substr (pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        trim(token);
        res.push_back (token);
    }

    res.push_back (s.substr (pos_start));
    return res;
}


const int bm_width = 8;
const int bm_height = 8;


typedef struct bitmap {
    int     width = 0;
    int     height = 0;
    int     data[];
} BM;

BM gBitmap = {
        .width = 8,
        .height = 8,
        .data = {
                0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 1, 0, 1, 1,
                0, 1, 1, 0, 0, 0, 1, 1,
                0, 1, 1, 0, 1, 1, 0, 0,
                0, 0, 0, 0, 1, 1, 0, 0,
                1, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 1, 1, 0, 0, 0, 0,
                0, 0, 1, 1, 0, 0, 0, 1,
        }
};

/* Helper macros for setting/getting bits from the bitmap */
#define GET_BIT(DATA,X,Y) DATA[((Y) * bm_width) + (X)]
#define SET_BIT(DATA,X,Y,B) DATA[((Y) * bm_width) + (x)] = B

/**
 * Load a bitmap from an external file.
 *
 * First line is formatted <width>,<height>\n
 *
 * Each line is comma separated values.
 *
 * @param bm_name
 * @return
 */

BM * load_bitmap(const char * bm_name, bool verbose = true) {
    BM * bm = nullptr;
    ifstream input(bm_name);
    if (input.is_open()) {
        vector<string> parsedString;
        string header;

        // Read the header.
        getline(input, header);
        parsedString = split(header, ",");

        if (parsedString.size() == 2) {
            int width = std::atoi(parsedString[0].c_str());
            int height = std::atoi(parsedString[1].c_str());

            bm = (struct bitmap *)malloc(sizeof(struct bitmap) + width * height * sizeof(int));
            if (bm) {
                string line;

                bm->width = width;
                bm->height = height;

                for (int y = 0 ; y < height ; y++) {
                    getline(input, line);
                    parsedString = split( line, "," );

                    for (int x = 0 ; x < width ; x++) {
                        SET_BIT(bm->data, x, y, std::atoi(parsedString[x].c_str()));
                    }
                }

                if (verbose) {
                    cout << "Loaded " << width << "X" << height << " bitmap from " << bm_name << '\n';
                }
            } else {
                cerr << "ERROR: Unable to allocate memory for bitmap.\n";
            }
        } else {
            cerr << "ERROR: Invalid format.\n";
            delete bm;
            return nullptr;
        }

    } else {
        cerr << "ERROR: Unable to open bitmap file.\n";
    }

    return bm;
}

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

/**
 * analyze the bitmap contained in the bitmap structure.
 * @param bm
 * @return
 */

int analyze_bitmap(const BM & bm) {
    return analyze_bitmap(const_cast<int*>(bm.data), bm.width, bm.height);
}

/**
 * Main entry point
 *
 * If the user passes in a filename, load the bitmap from the file.
 *
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, char * argv[]) {
    string bm_filename;

    if (argc > 1) {
        bm_filename = argv[1];
    }

    //int cnt = analyze_bitmap(bm_data, bm_width, bm_height);
    int cnt = 0;

    if (bm_filename.empty()) {
        cnt = analyze_bitmap(gBitmap);
    } else {
        BM * loadedBm = load_bitmap(bm_filename.c_str());

        if (loadedBm) {
            cnt = analyze_bitmap(*loadedBm);
            free(loadedBm);
        } else {
            cerr << "ERROR: Unable to load bitmap from file.\n";
        }
    }

    if (cnt > 0) {
        cout << "Analysis found " << cnt << " 2x2 squares of 1 bits in bitmap...\n";
    }

    return 0;
}