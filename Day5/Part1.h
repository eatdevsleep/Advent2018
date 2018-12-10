#pragma once
#include <iostream>
#include <utility>
#include <string>
#include <algorithm>
#include <fstream>
#include <regex>
#include <charconv>
#include <vector>
#include <math.h>
#include <unordered_map>
#include <list>
#include <sstream>

class Part1
{
public:
  static void Run()
  {
    std::ifstream inFile("input.txt");
    std::string instruction;
    std::list<char> charList;
    std::getline(inFile, instruction);
    std::copy(instruction.begin(), instruction.end(), back_inserter(charList));

    short charAStartIndex = (short)'A';
    short charaStartIndex = (short)'a';
    short charDifference = charaStartIndex - charAStartIndex;
    std::vector<char> reactionMatcher(256,';');
    for (short i = charAStartIndex; i < charAStartIndex+26; ++i)
    {
      char upper = (char)i;
      char lower = (char)i + charDifference;
      reactionMatcher[(short)lower] = upper;
      reactionMatcher[(short)upper] = lower;
    }

    bool reactions = false;
    do
    {
      reactions = false;
      auto previous = charList.begin();
      auto end = charList.end();
      auto current = previous;
      ++current;
  
      while(current != end)
      {
        if (*current == reactionMatcher[(int)(*previous)])
        {
          reactions = true;
          auto next = current;
          ++next;
          charList.erase(previous);
          charList.erase(current);
          previous = next;
          current = next;
          ++current;
        } 
        else
        {
          ++previous;
          ++current;
        }
      } 
    } while (reactions);

    std::ostringstream oss;
    std::copy(charList.begin(), charList.end(), std::ostream_iterator<char>(oss));
  
    std::cout << oss.str().length() << std::endl;
  }
};
