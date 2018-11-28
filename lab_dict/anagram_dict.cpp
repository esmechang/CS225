/**
 * @file anagram_dict.cpp
 * Implementation of the AnagramDict class.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include "anagram_dict.h"

#include <algorithm> /* I wonder why this is included... */
#include <fstream>

using std::string;
using std::vector;
using std::ifstream;

/**
 * Constructs an AnagramDict from a filename with newline-separated
 * words.
 * @param filename The name of the word list file.
 */
AnagramDict::AnagramDict(const string& filename)
{
    /* Your code goes here! */
    // vector<string> vecWords;
    // ifstream wordList(filename);
    // string word;
    // if (wordList.is_open()) {
    //   while (getline(wordList, word)) {
    //     vecWords.push_back(word);
    //   }
    // }
    // for (auto &vecIter : vecWords) {
    //   auto finder = dict.find(vecIter);
    //   if (finder == dict.end()) {
    //     std::vector<char> vectChar;
    //     for (size_t i = 0; i < vecIter.length(); i++) {
    //       vectChar.push_back(vecIter.at(i));
    //       std::sort(vectChar.begin(), vectChar.end());
    //       dict.insert(std::pair<string, std::vector<char>>(vecIter, vectChar));
    //     }
    //   }
    // }
    ifstream words(filename);
    string w;
    if (words.is_open()) {
      while(getline(words, w)) {
        string temp;
        sort(temp.begin(), temp.end());
        dict[temp].push_back(w);
      }
    }
}

/**
 * Constructs an AnagramDict from a vector of words.
 * @param words The vector of strings to be used as source words.
 */
AnagramDict::AnagramDict(const vector<string>& words)
{
    /* Your code goes here! */
    for (auto vecIter = words.begin(); vecIter != words.end(); vecIter++) {
      string temp = *vecIter;
      sort(temp.begin(), temp.end());
      dict[temp].push_back(*vecIter);
    }
}

/**
 * @param word The word to find anagrams of.
 * @return A vector of strings of anagrams of the given word. Empty
 * vector returned if no anagrams are found or the word is not in the
 * word list.
 */
vector<string> AnagramDict::get_anagrams(const string& word) const
{
    /* Your code goes here! */
    string w = word;
    sort(w.begin(), w.end());
    if (dict.find(w) != dict.end()) {
      return dict.find(w)->second;
    }
    return vector<string>();
}

// vector<string> AnagramDict::get_anagrams_helper(const string &word) const {
//   vector<string> output;
//   auto finder = dict.find(word);
//   if (finder != dict.end()) {
//     vector<char> vectChar = finder->second;
//     for (auto &dictIter : dict) {
//       if (dictIter.second == vectChar) {
//         output.push_back(dictIter.first);
//       }
//     }
//   }
//   return output;
// }

/**
 * @return A vector of vectors of strings. Each inner vector contains
 * the "anagram siblings", i.e. words that are anagrams of one another.
 * NOTE: It is impossible to have one of these vectors have less than
 * two elements, i.e. words with no anagrams are ommitted.
 */
vector<vector<string>> AnagramDict::get_all_anagrams() const
{
    /* Your code goes here! */
    vector<vector<string>> allAnagrams;
    for (auto &dictIter : dict) {
      vector<string> smolVect = get_anagrams(dictIter.first);
      if (smolVect.size() >= 2) {
        allAnagrams.push_back(smolVect);
      }
    }
    return allAnagrams;
}
