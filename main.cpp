#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <random>

int main() {
    std::string text, word, word_middle, output, not_alpha;
    int first_letter_index, last_letter_index, char_index, letter_index;

    getline(std::cin, text);

    std::stringstream ss(text);

    std::random_device seed;
    std::mt19937 gen(seed());

    while (ss >> word) {
        char_index = 0;
        letter_index = 0;
        last_letter_index = word.length() - 1;
        first_letter_index = 0;
        while (last_letter_index >= 0 and !isalpha(word[last_letter_index])) {
            last_letter_index--;
        }
        while (first_letter_index < last_letter_index and !isalpha(word[first_letter_index])) {
            first_letter_index++;
        }
        std::cout << first_letter_index << std::endl;
        std::cout << last_letter_index << std::endl;
        for (char c : word) {
            if (!isalpha(c)) {
                not_alpha+=c;
                char_index++;
                continue;
            }
            if (char_index == first_letter_index or char_index == last_letter_index) {
                char_index++; letter_index++;
                continue;
            }
            word_middle += c;
            char_index++; letter_index++;


        }
        shuffle(word_middle.begin(), word_middle.end(), gen);
        output+=word[first_letter_index]+word_middle+word[last_letter_index]+not_alpha+' ';
        word_middle.clear();
        not_alpha.clear();

    }
    std::cout << output;
}