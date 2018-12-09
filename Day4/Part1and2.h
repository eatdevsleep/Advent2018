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
class Part1and2
{
public:

  enum Action {
    BeginsShift,
    Sleeps,
    WakesUp
  };

  struct Record
  {
    std::string originalMessage;
    int guard;
    Action action;
    int year;
    short month;
    short hour;
    short day;
    short minute;
    long timecode;
  };

  static void Run()
  {
    std::ifstream inFile("input.txt");
    std::string instruction;
    try {
      std::regex regexExtractor("^\\[(\\d\\d\\d\\d)-(\\d\\d)-(\\d\\d)\\s(\\d\\d):(\\d\\d)\\]\\s(.+)$");
      std::regex regexGuardNo("^Guard\\s#(\\d+)\\sbegins\\sshift$");
      std::vector<Record> records;
      //[1518-11-01 00:00] Guard #10 begins shift
      //[1518-11-01 00:05] falls asleep
      //[1518-11-01 00:25] wakes up
      while (std::getline(inFile, instruction))
      {
        std::smatch matches;
        std::smatch guardMatches;
        // first part etl
        if (std::regex_search(instruction, matches, regexExtractor))
        {
          records.push_back(Record());
          Record &record = records.back();
          auto itr = matches.begin(); // assuming strings are of correct format
          record.timecode += (record.year = std::stoi(*++itr)) * 100000000l;
          record.timecode += (record.month = std::stoi(*++itr)) * 1000000l;
          record.timecode += (record.day = std::stoi(*++itr)) * 10000l;
          record.timecode += (record.hour = std::stoi(*++itr)) * 100l;
          record.timecode += (record.minute = std::stoi(*++itr)); // 1
          std::string message = *++itr;
          switch (message[0])
          {
          case'G':
            if (std::regex_search(message, guardMatches, regexGuardNo))
            {
              record.action = Action::BeginsShift;
              auto itr = guardMatches.begin(); // assuming strings are of correct format
              record.guard = std::stoi(*++itr);
            }
            break;
          case 'f':
            record.action = Action::Sleeps;
            break;
          case 'w':
            record.action = Action::WakesUp;
            break;
          }
          record.originalMessage.swap(instruction);
        }       
      }
      // get in correct order
      std::sort(records.begin(), records.end(), [](const Record & a, const Record & b) -> bool
      {
        return a.timecode < b.timecode; // assume no overlapping times
      });
      // Process event stream - record total minutes slept and exact minutes/frequency slept per guard
      std::unordered_map<int, int> totalSleepTracker; // guard#, mins
      std::unordered_map<int, int[60]> minuteSleepTracker; // <guard#,minute>,times
      int currentGuard = -1;
      int lastSleepTime = -1;
      for (auto& record : records)
      {
        switch (record.action)
        {
        case Action::BeginsShift:
          //  
          if (currentGuard != -1 && lastSleepTime != -1)
          {
            totalSleepTracker[currentGuard] += 60 - lastSleepTime; // find how many minutes remained in hour
            for (int i = lastSleepTime; i < 60; ++i)
            {
              minuteSleepTracker[currentGuard][i]++;
            }
          }
          currentGuard = record.guard;
          lastSleepTime = -1;
          break;
        case Action::Sleeps:
          lastSleepTime = record.minute;
          break;
        case Action::WakesUp:
          if (currentGuard != -1 && lastSleepTime != -1)
          {
            totalSleepTracker[currentGuard] += record.minute - lastSleepTime;
            for (int i = lastSleepTime; i < record.minute; ++i)
            {
              minuteSleepTracker[currentGuard][i]++;
            }
          }
          lastSleepTime = -1;
          break;
        }
      }

      // find guard who slept most
      int mostSleepGuard;
      int maxMinutesSleep = 0;
      for (auto& pair : totalSleepTracker)
      {
        if (pair.second > maxMinutesSleep)
        {
          mostSleepGuard = pair.first;
          maxMinutesSleep = pair.second;
        }
      }
      std::cout << "Guard with most sleep: " <<  mostSleepGuard << std::endl;

      // find most frequent minute slept by the guard who slept most
      int maxOccurances = 0;
      int maxMinute = -1;
      int* occurances = minuteSleepTracker[mostSleepGuard];
      for (int i = 0; i < 60; ++i)
      {
        if (occurances[i] > maxOccurances)
        {
          maxOccurances = occurances[i];
          maxMinute = i;
        }
      }
      std::cout << "Minute most asleep: " << maxMinute << std::endl;

      // find most frequent minute slept by a single guard
      int guardWithMostOccurancesOfAMinute = -1;
      for (auto& specificGuardMinuteSleepTracker : minuteSleepTracker)
      {
        int guardNo = specificGuardMinuteSleepTracker.first;
        int* occurances = specificGuardMinuteSleepTracker.second;
        for (int i = 0; i < 60; ++i)
        {
          if (occurances[i] > maxOccurances)
          {
            maxOccurances = occurances[i];
            maxMinute = i;
            guardWithMostOccurancesOfAMinute = guardNo;
          }
        }
      }

      std::cout << "part 1: " << mostSleepGuard * maxMinute << std::endl;

      std::cout << "part 2: " << guardWithMostOccurancesOfAMinute * maxMinute << std::endl;

    }
    catch (const std::regex_error& e) {
      std::cout << "regex_error caught: " << e.what() << '\n';
      if (e.code() == std::regex_constants::error_brack) {
        std::cout << "The code was error_brack\n";
      }
    }
  }
};



