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
#include <chrono>
#include <ctime>
#include <deque>

class Part1and2
{
public:
  static void Run()
  {
    std::ifstream inFile("input.txt");
    std::string instruction;
    std::getline(inFile, instruction);
    short charAStartIndex = (short)'A';
    short charaStartIndex = (short)'a';
    short charDifference = charaStartIndex - charAStartIndex;
    std::vector<char> reactionMatcher(256, ';');
    for (short i = charAStartIndex; i < charAStartIndex + 26; ++i)
    {
      char upper = (char)i;
      char lower = (char)i + charDifference;
      reactionMatcher[(short)lower] = upper;
      reactionMatcher[(short)upper] = lower;
    }
    std::string reactedPolymers = std::move(ReactPolymers(instruction, reactionMatcher));
    // part A
    std::cout << reactedPolymers.length() << std::endl;

    // part B    
    short charStartIndex = (short)'a';
    int minLength = INT32_MAX;
    for (short i = charStartIndex; i < charStartIndex + 26; ++i)
    {
      std::string filteredInstruction;
      char filterChar = (char)i;
      auto otherCase = reactionMatcher[(short)filterChar];
      std::copy_if(instruction.begin(), instruction.end(), back_inserter(filteredInstruction), [&](char i) {return i != filterChar && i != otherCase; });
      filteredInstruction = std::move(ReactPolymers(filteredInstruction, reactionMatcher));
      if (filteredInstruction.length() < minLength)
      {
        minLength = filteredInstruction.length();
      }     
    }
    std::cout << "minLength: " << minLength << std::endl;

  }
  static std::string ReactPolymers(std::string &instruction, std::vector<char> &reactionMatcher)
  {
    std::list<char> charList;
    std::copy(instruction.begin(), instruction.end(), back_inserter(charList)); 

    auto start = std::chrono::system_clock::now();
    bool reactions = false;
    do
    {
      reactions = false;
      auto previous = charList.begin();
      auto end = charList.end();
      auto current = previous;
      ++current;

      while (current != end)
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
          if (current == end) break;
          ++current;
        }
        else
        {
          ++previous;
          ++current;
        }
      }
    } while (reactions);
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
    std::cout << "elapsed time: " << elapsed_seconds.count() << "s\n";

    std::ostringstream oss;
    std::copy(charList.begin(), charList.end(), std::ostream_iterator<char>(oss));
    auto reacted = std::move(oss.str());
    return reacted;
  }
};
