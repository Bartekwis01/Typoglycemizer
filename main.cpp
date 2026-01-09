#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <random>

int main() {
    std::string text, word, word_middle, output, not_alpha, old_word_middle;
    int first_letter_index, last_letter_index, char_index;
    bool FORCE_SHUFFLE = true; //if true will force shuffling the middle letters of a word if possible

    getline(std::cin, text);

    std::stringstream ss(text);

    std::random_device seed;
    std::mt19937 gen(seed());

    while (ss >> word) {
        char_index = 0;
        last_letter_index = word.length() - 1;
        first_letter_index = 0;
        while (last_letter_index >= 0 and !isalpha(word[last_letter_index])) {
            last_letter_index--;
        }
        while (first_letter_index < last_letter_index and !isalpha(word[first_letter_index])) {
            first_letter_index++;
        }
        if (first_letter_index == 0 and !isalpha(word[0])) {
            first_letter_index = -1;
        }
        for (char character : word) {
            if (!isalpha(character)) {
                not_alpha+=character;
                char_index++;
                continue;
            }
            if (char_index == first_letter_index or char_index == last_letter_index) {
                char_index++;
                continue;
            }
            word_middle += character;
            char_index++;


        }
        if (word.length() >= 4) {
            if (FORCE_SHUFFLE) {
                old_word_middle = word_middle;
                while (word_middle == old_word_middle) {
                    std::ranges::shuffle(word_middle.begin(), word_middle.end(), gen);
                }
            }
            else {
                std::ranges::shuffle(word_middle.begin(), word_middle.end(), gen);
            }
        }
        if (first_letter_index != -1) {
            output+=word[first_letter_index];
        }
        output+=word_middle;
        if (last_letter_index != -1) {
            output+=word[last_letter_index];
        }
        output+=not_alpha+' ';
        word_middle.clear();
        not_alpha.clear();

    }
    std::cout << output;
}