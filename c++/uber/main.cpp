//
// Created by muman on 2/25/19.
//

// Group a list of words into a list of lists of words by anagrams
// Input: 'dog', 'elvis', 'forest', 'fortes', 'fortess', 'foster', 'goat', 'god', 'heros', 'horse', 'lives', 'shore', 'softer'
// Output
// [
//  ['elvis', 'lives'],
//  ['forest', 'fortes', 'foster', 'softer'],
//  ['heros', 'horse', 'shore'],
//  ['dog', 'god'],
//  ['goat']
// ]

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

typedef std::vector<std::string> string_vector;
typedef std::vector<string_vector> result_vector;


/**
 *
 * @param input
 * @param output
 * @return
 */
bool get_anagrams(const string_vector & input, result_vector & output) {
    std::map<std::string, string_vector>    wordMap;

    for (auto const & word : input) {
        string sorted = word;
        std::sort(sorted.begin(), sorted.end());

        wordMap[sorted].push_back(word);
    }

    for (auto const & pairs : wordMap) {
        output.push_back(pairs.second);
    }

    return (!output.empty());
}

int main() {
    string_vector input_words = {
            "dog",
            "elvis",
            "forest",
            "fortes",
            "fortess",
            "foster",
            "goat",
            "god",
            "heros",
            "horse",
            "lives",
            "shore",
            "softer"
    };
    result_vector output_vec;

    if (get_anagrams(input_words, output_vec)) {
        for (auto const & subvec : output_vec) {
            cout << "[ ";
            for (auto const & word: subvec) {
                cout << word << " ";
            }
            cout << "]\n";
        }
    }

    return 0;
}
