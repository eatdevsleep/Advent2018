#pragma once
#include <iostream>
#include <utility>
#include <string>
#include <algorithm>
#include <fstream>
#include <functional>
#include <iterator>
#include <unordered_set>
using namespace std;
class Part2
{
public:
  

  static void Run()
  {
    ifstream inFile("input.txt");
    vector<string> codes;
    codes.reserve(1000);
    istream_iterator<string> eos;              // end-of-stream iterator
    istream_iterator<string> iit(inFile);
    copy(iit, eos, back_inserter(codes));

    unordered_set<string> hits;
    bool iterationHasLeft = true;
    for (int charMissing = 0; iterationHasLeft; ++charMissing)
    {
      hits.clear();
      iterationHasLeft = false;

      auto end = hits.end();
      for (auto& code : codes)
      {
        int codeLength = code.length();
        if (codeLength > charMissing+1)
        {
          int secondStringLength = codeLength - charMissing - 1;
          auto subString = code.substr(0, charMissing).append(code.substr(charMissing + 1, secondStringLength));
          
          if (auto iter = hits.find(subString);  iter == end)
          {
            iterationHasLeft = true;
            hits.insert(subString);
          }
          else
          {
            iterationHasLeft = true;
            cout << subString << endl;
          }
        }
      }
    }
  }
};

