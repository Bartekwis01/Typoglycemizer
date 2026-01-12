#include "typoglycemia.h"

#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <random>
#include <vector>
#include <ranges>

static std::random_device seed;
static std::mt19937 gen(seed());

std::string format(std::string text, bool REPLACE_UNDERSCORES, bool REPLACE_HYPHENS) {
    if (REPLACE_UNDERSCORES) {
        std::ranges::replace(text, '_', ' ');
    }
    if (REPLACE_HYPHENS) {
        std::ranges::replace(text, '-', ' ');
    }
    return text;

}

std::string typoglycemizeWord(std::string word, bool FORCE_SHUFFLE) {
    int char_index = 0;
    int last_letter_index = word.length() - 1;
    int first_letter_index = 0;
    std::string not_alpha, word_middle, output;

    //compute last letter index
    while (last_letter_index >= 0 and !isalpha(word[last_letter_index])) {
        last_letter_index--;
    }
    //compute first letter index
    while (first_letter_index < last_letter_index and !isalpha(word[first_letter_index])) {
        first_letter_index++;
    }
    if (first_letter_index == 0 and !isalpha(word[0])) {
        first_letter_index = -1;
    }

    //handle not letters
    for (char character : word) {
        if (isalpha(character) and char_index != first_letter_index and char_index != last_letter_index) {
            not_alpha.push_back('\0'); //closest to empty
            word_middle += character;
        }
        else { //isn't alpha
            not_alpha.push_back(character);
        }
        char_index++;
    }

    //shuffle the middle
    if (word.length() >= 4) {
        if (FORCE_SHUFFLE) {
            std::string old_word_middle = word_middle;
            while (word_middle == old_word_middle) {
                std::ranges::shuffle(word_middle.begin(), word_middle.end(), gen);
            }
        }
        else {
            std::ranges::shuffle(word_middle.begin(), word_middle.end(), gen);
        }
    }

    //re-construct the word
    int j = 0;
    for (int i = 0; i < word.length(); i++) {
        if (i==first_letter_index or i==last_letter_index) {
            output += word[i];
        }
        else if (not_alpha[i] != '\0') { //closest to empty
            output+= not_alpha[i];
        }
        else {
            output+= word_middle[j];
            j++;
        }
    }
    return output;
}

std::string typoglycemize(std::string text, bool FORCE_SHUFFLE, bool REPLACE_UNDERSCORES, bool REPLACE_HYPHENS) {
    std::string word, output;
    std::vector<std::string>typoglycemized; //vector of the words that make up the text

    text = format(text, REPLACE_UNDERSCORES, REPLACE_HYPHENS); //formatting

    std::stringstream ss(text);

    while (ss >> word) {
        typoglycemized.push_back(typoglycemizeWord(word, FORCE_SHUFFLE));
    }
    for (int i = 0; i < typoglycemized.size(); i++) {
        output += typoglycemized[i];
        if (i != typoglycemized.size() - 1) {
            output += " ";
        }
    }
    return output;
}