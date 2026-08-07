#include <string>
#include <vector>
#include <array>
#include <algorithm>
#include <iostream>

using namespace std;

// This is the Master's API interface.
// You should not implement it, or speculate about its implementation
// class Master
// {
// public:
//   int guess(string word);
// };

class Solution
{
public:
  void findSecretWord(vector<string> &wordlist, Master &master)
  {
    vector<string> filteredWords = wordlist;

    array<vector<char[6]>, 7> matchCountMapCache;
    while (true)
    {
      string *guessedWord;
      int minMaxMatchCount = 100;
      array<vector<char[6]>, 7> minMaxMatchCountMap;
      for (auto &word : filteredWords)
      {
        auto maxMatchCount = getMatchCountMap(word, filteredWords, matchCountMapCache);
        if (maxMatchCount < minMaxMatchCount)
        {
          minMaxMatchCount = maxMatchCount;
          minMaxMatchCountMap = move(matchCountMapCache);
          guessedWord = &word;
        }
      }
      int m = master.guess(*guessedWord);
      if (m == 6)
      {
        return;
      }
      filteredWords = minMaxMatchCountMap[m];
    }
  }

  {
    int getMatchCountMap(const string &word, const vector<string> &wordlist, array<vector<char[6]>, 7> &matchCountMap) int maxMatchCount = 0;
    for_each(begin(matchCountMap), end(matchCountMap), [](auto &map)
             { map.clear(); });
    for (auto &word2 : wordlist)
    {
      int m = match(word, word2);
      matchCountMap[m].push_back(word2);
      maxMatchCount = max(maxMatchCount, int(matchCountMap[m].size()));
    }
    return maxMatchCount;
  }

  int match(const string &a, const string &b)
  {
    int c = 0;
    for (int i = 0; i < 6; ++i)
    {
      if (a[i] == b[i])
        ++c;
    }
    return c;
  }
};