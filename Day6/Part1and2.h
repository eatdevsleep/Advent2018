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
#include <math.h>
#include <array>
#include <assert.h>
#include <map>

using namespace std;

class Part1and2
{
public:
  static void Run()
  {
    std::ifstream inFile("input.txt");
    std::string coord;
    std::vector<std::tuple<int,int, int>> coords; //id, x, y
    coords.reserve(50);
    int id = -1;
    while (std::getline(inFile, coord))
    {
      int delimiter = coord.find(",");
      auto tuple = std::make_tuple(
        ++id, // id
        std::stoi(coord.substr(0, delimiter)), //x
        std::stoi(coord.substr(delimiter + 1, coord.length()))); //y

      coords.push_back(std::move(tuple));
    }

    const auto[_id1, minX, _y1] = *std::min_element(coords.begin(), coords.end(), [](auto& a, auto& b) {return std::get<1>(a) < std::get<1>(b); });
    const auto[_id2, _x1, minY] = *std::min_element(coords.begin(), coords.end(), [](auto& a, auto& b) {return std::get<2>(a) < std::get<2>(b); });
    const auto[_id3, maxX, _y2] = *std::max_element(coords.begin(), coords.end(), [](auto& a, auto& b) {return std::get<1>(a) < std::get<1>(b); });
    const auto[_id4, _x2, maxY] = *std::max_element(coords.begin(), coords.end(), [](auto& a, auto& b) {return std::get<2>(a) < std::get<2>(b); });

    const int sizeX = maxX - minX + 1;
    const int sizeY = maxY - minY + 1;
    const auto indexer = [=](std::vector<int>& matrix, int x, int y) -> int& 
    {
      int coord = (y - minY)*sizeX + (x - minX);  
      return matrix[coord]; 
    };

    // part 1
    std::vector<int> distances(sizeX*sizeY, INT32_MAX);
    std::vector<int> closestCoord(sizeX*sizeY, -1);
    // part 2
    std::vector<int> totalDistances(sizeX*sizeY, 0);

    //test
    assert(INT32_MAX == indexer(distances,minX,minY));
    assert(INT32_MAX == indexer(distances, maxX, minY));
    assert(INT32_MAX == indexer(distances, minX, maxY));
    assert(INT32_MAX == indexer(distances, maxX, maxY));

    const auto dist = [](int x1, int y1, int x2, int y2) {return std::abs(x2 - x1) + std::abs(y2 - y1); };
    const int JointId = -2;

    for (auto coord : coords)
    {
      const auto[coordId, coordX, coordY] = coord;
      for (int x = minX; x <= maxX; ++x)
      {
        for (int y = minY; y <= maxY; ++y)
        {
          int manhattanDist = dist(coordX, coordY, x, y);
          indexer(totalDistances, x, y) += manhattanDist;
          int& currMinDist = indexer(distances, x, y);
          if (currMinDist > manhattanDist)
          {
            currMinDist = manhattanDist;
            indexer(closestCoord, x, y) = coordId;
          }
          else if (currMinDist == manhattanDist)
          {
            indexer(closestCoord, x, y) = JointId; // means 2 coords have same dist
          }
        }
      }
    }

    std::map<int, int> idCounts;
    for (int& id : closestCoord)
    {
      idCounts[id]++;
    }

    auto& maxElement = *std::max_element (idCounts.begin(), idCounts.end(), [](auto& a, auto& b) {return a.second < b.second; });
    std::cout << "largest area: " << maxElement.second << " by id: " << maxElement.first << std::endl;

    const int coordCount = coords.size();
    const int targetMaxTotalDistance = 10000-1;

    int totalCount = 0;

    // total distance is:
    // count of all items in grid boundary with total under max
    totalCount += std::count_if(totalDistances.cbegin(), totalDistances.cend(), [=](auto dist) {return dist <= targetMaxTotalDistance;});
    // + for each edge value (9999 - each edge total dist) / #coords
    // minx+1 to maxX-1, minY and maxY
    for (int x = minX + 1; x < maxX; ++x) {
      if(int edgeDist = indexer(totalDistances, x, minY); edgeDist < targetMaxTotalDistance)
        totalCount += (targetMaxTotalDistance - edgeDist) / coordCount;
      if (int edgeDist = indexer(totalDistances, x, maxY); edgeDist < targetMaxTotalDistance)
        totalCount += (targetMaxTotalDistance - edgeDist) / coordCount;
    }
    // minx and maxX, minY+1 to maxY-1
    for (int y = minY + 1; y < maxY; ++y) {
      if (int edgeDist = indexer(totalDistances, minX, y); edgeDist < targetMaxTotalDistance)
        totalCount += (targetMaxTotalDistance - edgeDist) / coordCount;
      if (int edgeDist = indexer(totalDistances, maxX, y); edgeDist < targetMaxTotalDistance)
        totalCount += (targetMaxTotalDistance - edgeDist) / coordCount;
    }
    // + for each corner value (edge total above)^2 / 2
    if (int edgeDist = indexer(totalDistances, minX, minY); edgeDist < targetMaxTotalDistance)
      totalCount += ((targetMaxTotalDistance - edgeDist) / coordCount) ^ 2 / 2; // topleft
    if (int edgeDist = indexer(totalDistances, maxX, minY); edgeDist < targetMaxTotalDistance)
      totalCount += ((targetMaxTotalDistance - edgeDist) / coordCount) ^ 2 / 2; // topright
    if (int edgeDist = indexer(totalDistances, minX, maxY); edgeDist < targetMaxTotalDistance)
      totalCount += ((targetMaxTotalDistance - edgeDist) / coordCount) ^ 2 / 2; // bottomleft
    if (int edgeDist = indexer(totalDistances, maxX, maxY); edgeDist < targetMaxTotalDistance)
      totalCount += ((targetMaxTotalDistance - edgeDist) / coordCount) ^ 2 / 2; // bottomright

    std::cout << "total Count: " << totalCount << " in zone with distances under: " << targetMaxTotalDistance + 1 << std::endl;
  }
};

