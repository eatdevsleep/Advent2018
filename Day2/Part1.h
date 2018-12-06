#pragma once

#include <iostream>
#include <utility>
#include <string>
#include <algorithm>
#include <fstream>

class Part1
{
public:

  static std::pair<bool, bool> CheckSum(std::string& code)
  {
    int stringln = code.length();
    bool two = false;
    bool three = false;
    std::sort(code.begin(), code.end());
    int count = 1;
    for (int i = 1; i < stringln & (!two|!three); ++i)
    {
      if (code[i] == code[i - 1])
        ++count;
      else
      {
        if (count == 2) two = true;
        if (count == 3) three = true;
        count = 1;
      }
    }
    return std::make_pair(two, three);
  }

  static void Run()
  {
    std::ifstream inFile("input.txt");
    int twos = 0;
    int threes = 0;
    std::string code;
    while (inFile >> code)
    {
      const auto[aTwo, aThree] = CheckSum(code);
      twos += aTwo;
      threes += aThree;
    }
    std::cout << twos * threes << std::endl;
  }
};

