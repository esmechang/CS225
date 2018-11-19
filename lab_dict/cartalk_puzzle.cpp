/**
 * @file cartalk_puzzle.cpp
 * Holds the function which solves a CarTalk puzzler.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include <fstream>

#include "cartalk_puzzle.h"

using namespace std;

/**
 * Solves the CarTalk puzzler described here:
 * http://www.cartalk.com/content/wordplay-anyone.
 * @return A vector of (string, string, string) tuples
 * Returns an empty vector if no solutions are found.
 * @param d The PronounceDict to be used to solve the puzzle.
 * @param word_list_fname The filename of the word list to be used.
 */
vector<std::tuple<std::string, std::string, std::string>> cartalk_puzzle(PronounceDict d,
                                    const string& word_list_fname)
{
    vector<std::tuple<std::string, std::string, std::string>> ret;

    /* Your code goes here! */
  vector< StringTriple> output;
	vector< string > vectWords;
	ifstream wordList(word_list_fname);
	string word;

	if(wordList.is_open()) {
   	while(getline(wordList, word)) {
			if(word.length() == 5)
				vectWords.push_back(word);
		}
	}

	for(auto & each : vectWords) {
		std:: string remove1 = each.substr(1);
		std:: string remove2;

		remove2.append(each.begin(),each.begin()+1);
		remove2.append(remove1.begin()+1,remove1.end());

		if(d.homophones(each, remove1)&&d.homophones(each, remove2)&&d.homophones(remove1, remove2)) {
			StringTriple result;
			std::get<0>(result) = each;
			std::get<1>(result) = remove1;
			std::get<2>(result) = remove2;
			output.push_back(result);
		}
	}
    return output;
}
