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

class Part1
{
public:

  struct Rect {
    int number;
    int coordX;
    int coordY;
    int dimX;
    int dimY;
  };

  static void Run()
  {
    std::ifstream inFile("input.txt");
    std::string instruction;
    try {
      std::regex regexExtractor("^#(\\d+)\\s@\\s(\\d+),(\\d+):\\s(\\d+)x(\\d+)$");
      std::vector<Rect> rects;
      rects.reserve(1000);
      int maxX = 0;
      int maxY = 0;
      while (std::getline(inFile, instruction))
      {
        std::smatch matches;
        if (std::regex_search(instruction, matches, regexExtractor))
        {
          rects.push_back(Rect());
          Rect &rect = rects.back();
          auto itr = matches.begin(); // assuming strings are of correct format
          rect.number  = std::stoi(*++itr);
          rect.coordX = std::stoi(*++itr);
          rect.coordY = std::stoi(*++itr);
          rect.dimX = std::stoi(*++itr);
          rect.dimY = std::stoi(*++itr);

          maxX = std::max(maxX, rect.coordX + rect.dimX);
          maxY = std::max(maxY, rect.coordY + rect.dimY);

        }
      }
      std::vector<short> grid(maxX*maxY, 0);
      int count = 0;
      for (const auto& rect : rects)
      {
        for (int i = rect.coordX; i < (rect.dimX + rect.coordX); ++i)
        {
          for (int j = rect.coordY; j < (rect.dimY + rect.coordY); ++j)
          {
            if (2 == ++grid[j*maxX + i])
              ++count;
          }
        }
      }
      std::cout << count << std::endl;
    }
    catch (const std::regex_error& e) {
      std::cout << "regex_error caught: " << e.what() << '\n';
      if (e.code() == std::regex_constants::error_brack) {
        std::cout << "The code was error_brack\n";
      }
    }
  }
};

