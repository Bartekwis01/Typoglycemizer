#include <iostream>
#include "typoglycemia.h"

int main() {
    std::string text;
    getline(std::cin, text); //gets whole line instead of only 1 word to space
    std:: string typoglycemized_text = typoglycemize(text, true, true, true);
    std::cout << typoglycemized_text << std::endl;
    std::cout << "Press any key to close...";
    std::cin.get();
}
