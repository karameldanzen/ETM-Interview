/* Given an arbitrary text document written in English, write a program that will generate a
 * concordance, i.e. an alphabetical list of all word occurrences, labeled with word
 * frequencies.
 *
 * Bonus: label each word with the sentence numbers in which each occurrence appeared.
 * 
 */

#include "main.h"

// helper function that returns the opposite of isalpha.
bool isNotAlphaOrPeriod(char c) {
    return !(c == '.' || isalpha(c));
}

// helper function that takes a string and renders it lowercase
std::string stringToLowercase(std::string s)
{
    std::transform(s.begin(), s.end(), s.begin(), [](unsigned char c) { return std::tolower(c); });
    return s;
}

// helper function that takes a string and strips it of all nonalphabetical characters
std::string removeNonAlphabetOrPeriod(std::string s)
{
    s.erase(std::remove_if(s.begin(), s.end(), isNotAlphaOrPeriod), s.end());
    return s;
}

// given a valid filestream, parse it into a concordance map.
void parseIntoMap(std::fstream& f)
{
    std::map<std::string, std::pair<int, std::vector<int>>> concordanceMap;
    std::string word = "";
    int sentenceNumber = 1;
    while (f >> word)
    {
        std::set<std::string> knownAbbreviations{ "al.", "e.g.", "etc.", "i.e."};
        // check to ensure word isn't a known abbreviation listed in the vector above and also ends a sentence.
        // in this context, a sentence can only be ended by a period, not a newline.
        word = stringToLowercase(word);
        word = removeNonAlphabetOrPeriod(word);

        // ensure known abbreviations listed above aren't stripped of their trailing period
        if (word.back() == '.' && knownAbbreviations.find(word) == knownAbbreviations.end())
        {
            word.resize(word.size() - 1);
            sentenceNumber++;
        }

        // not found, populate initial pair with a count of 1 and the current sentence number
        if (concordanceMap.find(word) == concordanceMap.end() && !word.empty())
        {
            std::vector<int> tempVector;
            tempVector.push_back(sentenceNumber);
            std::pair<int, std::vector<int>> tempPair;
            tempPair.first = 1;
            tempPair.second = tempVector;
            concordanceMap.insert_or_assign(word, tempPair);
        }

        // was found, update current pair with new count and append the current sentence number to the vector
        else if (concordanceMap.find(word) != concordanceMap.end())
        {
            std::pair<int, std::vector<int>> tempPair = concordanceMap[word];
            tempPair.first++;
            std::vector<int> tempVector = tempPair.second;
            tempVector.push_back(sentenceNumber);
            tempPair.second = tempVector;
            concordanceMap.insert_or_assign(word, tempPair);
        }
    }

    // print to console
    for (auto const& pair : concordanceMap)
    {
        std::cout << pair.first << ": { " << pair.second.first << " : ";
        std::vector<int> tempVector = pair.second.second;
        for (int i = 0; i < tempVector.size(); i++)
        {
            if (i == (tempVector.size() - 1))
            {
                std::cout << tempVector.at(i) << " }" << std::endl;
            }
            else
            {
                std::cout << tempVector.at(i) << ", ";
            }
        }
    }
}

int main()
{
    std::fstream fileStream;
    std::string fileName = "";

    std::cout << std::filesystem::current_path() << std::endl;
    std::cout << "Enter filename, or enter exit to quit. " << std::endl;

    while (!fileStream.is_open())
    {
        std::cout << "Enter filename: ";
        std::getline(std::cin, fileName);
        if (fileName == "exit")
        {
            return 0;
        }
        fileStream.open(fileName);
        if (!fileStream.is_open()) // file provided is invalid
        {
            std::cout << "Invalid file." << std::endl;
        }
    }

    std::cout << "Concordance for " << fileName << ": " << std::endl;

    parseIntoMap(fileStream);

    std::cout << std::endl << "Press enter to exit." << std::endl;
    std::getline(std::cin, fileName);
	return 0;
}
