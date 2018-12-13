// ------------------------------------------------------------------------------------------
// removes all puncuation in a given string, and then returns that string
std::string replacePuncuation(std::string);

// splits a given string up given into sentences (with punctuation --> . ! ?), and returns a vector of those sentences
std::vector<std::string> splitParagraph(std::string);

// capitalize's the first letter only of a given string, and then returns that String
std::string capitalizeWord(std::string);

// adds a puncuation string to the end of a given string, and then returns that string.
std::string addPuncuation(std::string, std::string);

// counts the number of times a given character shows up in a given string, and returns that number
int countChar(std::string, char);

// returns true if the string contains punctuation (. ! ?) or false otherwise
bool puncInString(std::string);
// ------------------------------------------------------------------------------------------
