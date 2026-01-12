#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <random>
#include <vector>

std::random_device seed;
std::mt19937 gen(seed());

std::string format(std::string text, bool REPLACE_UNDERSCORES = true, int REPLACE_HYPHENS = true) {
    if (REPLACE_UNDERSCORES) {
        std::ranges::replace(text, '_', ' ');
    }
    if (REPLACE_HYPHENS) {
        std::ranges::replace(text, '-', ' ');
    }
    return text;

}

std::string Typoglycemize(std::string word, bool FORCE_SHUFFLE = true) {
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

int main() {
    std::string text, word;
    std::vector<std::string>typoglycemized;
    getline(std::cin, text);

    text = format(text); //formatting

    std::stringstream ss(text);

    while (ss >> word) {
        typoglycemized.push_back(Typoglycemize(word));
    }
    for (int i = 0; i < typoglycemized.size(); i++) {
        std::cout << typoglycemized[i];
        if (i != typoglycemized.size() - 1) {
            std::cout << " ";
        }
    }
}