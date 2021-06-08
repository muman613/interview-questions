#include <vector>
#include <iostream>

using namespace std;

class Solution {
public:
    vector<vector<int>> flipAndInvertImage(vector<vector<int>>& image) {
        vector<vector<int>> output;


        for (const auto & row : image) {
            vector<int> t;
            // reverse each row
            for (auto iter = row.rbegin() ; iter != row.rend() ; iter++) {
                t.push_back((*iter == 0)?1:0);
            }

            output.push_back(t);
        }

        return output;
    }
};

int main(int argc, char * argv[]) {
    Solution s;

    vector<vector<int>> image_1 = { {1,1,0}, {1,0,1}, {0,0,0} };
    vector<vector<int>> image_2 = { {1,1,0,0},{1,0,0,1},{0,1,1,1},{1,0,1,0} };

    auto inverted_1 = s.flipAndInvertImage(image_1);

    std::cout << "Image 1" << std::endl;
    for (const auto & row : inverted_1) {
        for (const auto & col : row) {
            std::cout << col << " ";
        }
        std::cout << std::endl;
    }
    auto inverted_2 = s.flipAndInvertImage(image_2);

    std::cout << "Image 2" << std::endl;
    for (const auto & row : inverted_2) {
        for (const auto & col : row) {
            std::cout << col << " ";
        }
        std::cout << std::endl;
    }
    return 0;
}