#include <regex>
#include <string>
#include <vector>
// ------------------------------------------------------------------------------------------
#include "TextTools.hpp"
/*
---------------------------------------------------------------------------------------------
*/
std::string replacePuncuation(std::string str) {
  std::regex r("[.!?]"); // [ . ! ? ] ---> punctuation list

	std::string result;
	regex_replace(back_inserter(result), str.begin(), str.end(), r, "");

  return result;
}
// ------------------------------------------------------------------------------------------
std::vector<std::string> splitParagraph(std::string paragraph) {
  std::vector<std::string> sentences = std::vector<std::string>();

	std::regex punc("[.!?]");
	std::smatch match;

	while (regex_search(paragraph, match, punc)) {
		for (auto x : match) {
			size_t pos = paragraph.find(x);
			sentences.push_back(paragraph.substr(0, pos+1));
		}
		paragraph = match.suffix().str();
	}
	return sentences;

}
// ------------------------------------------------------------------------------------------
std::string capitalizeWord(std::string word) {
	std::string str = word;

  str[0] = toupper(str[0]);

  return str;
}
// ------------------------------------------------------------------------------------------
std::string addPuncuation(std::string word, std::string punc) {
	std::string str = word + punc;

  return str;
}
// ------------------------------------------------------------------------------------------
int countChar(std::string word, char c) {
  int count = 0;

  for (const char& each_char : word) {
		if (each_char == c) {
			count++;
		}
	}

  return count;
}
// ------------------------------------------------------------------------------------------
bool puncInString(std::string str) {
	for (auto eachChar : str) {
		if (eachChar == '!' || eachChar == '.' || eachChar == '?') {
			return true;
		}
	}
	return false;
}
// ------------------------------------------------------------------------------------------
