#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <random>

int main() {
    std::string text, word, output;
    bool FORCE_SHUFFLE = true; //if true will force shuffling the middle letters of a word if possible

    getline(std::cin, text);

    std::stringstream ss(text);

    std::random_device seed;
    std::mt19937 gen(seed());

    while (ss >> word) {
        int char_index = 0;
        int last_letter_index = word.length() - 1;
        int first_letter_index = 0;
        std::string not_alpha, word_middle, old_word_middle;
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
            if (isalpha(character) and char_index != first_letter_index and char_index != last_letter_index) {
                not_alpha.push_back('\0');
                word_middle += character;
            }
            else { //isn't alpha
                not_alpha.push_back(character);
            }
            char_index++;
        }
        if (word.length() >= 4) {
            old_word_middle = word_middle;
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
        int j = 0;
        for (int i = 0; i < word.length(); i++) {
            if (i==first_letter_index or i==last_letter_index) {
                output += word[i];
            }
            else if (not_alpha[i] != '\0') { //closest to truly empty
                output+= not_alpha[i];
            }
            else {
                output+= word_middle[j];
                j++;
            }
        }
        output += ' ';
        not_alpha.clear(); word_middle.clear();


    }
    std::cout << output;
}