#pragma once
#include <string>

std::string format(std::string text);
std::string typoglycemizeWord(std::string word);
std::string typoglycemize(std::string text, bool FORCE_SHUFFLE = true, bool REPLACE_UNDERSCORES = true, bool FORCE_HYPHENS = true);