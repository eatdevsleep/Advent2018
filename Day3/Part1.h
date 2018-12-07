#pragma once

#include <iostream>
#include <utility>
#include <string>
#include <algorithm>
#include <fstream>
#include <regex>
#include <charconv>
#include <vector>

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
      std::regex regexExtractor("/#(?<number>([0-9])+)\s@\s(?<coordX>[0-9]+),(?<coordY>[0-9]+):\s(?<dimX>[0-9]+)x(?<dimY>[0-9]+)/gi");
      std::vector<Rect> rects;
      rects.reserve(1000);
      while (inFile >> instruction)
      {
        std::smatch matches;
        if (std::regex_search(instruction, matches, regexExtractor))
        {
          rects.push_back(Rect());
          Rect &rect = rects.back();
          auto itr = matches.begin(); // assuming strings are of correct format
          rect.number  = std::stoi(*itr++);
          rect.coordX = std::stoi(*itr++);
          rect.coordY = std::stoi(*itr++);
          rect.dimX = std::stoi(*itr++);
          rect.dimY = std::stoi(*itr++);
          rects.push_back(rect);
        }

      }

    }
    catch (const std::regex_error& e) {
      std::cout << "regex_error caught: " << e.what() << '\n';
      if (e.code() == std::regex_constants::error_brack) {
        std::cout << "The code was error_brack\n";
      }
    }
  }
};

