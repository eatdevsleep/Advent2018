// Day1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
//

#include "pch.h"
#include <iostream>
#include <fstream>
#include <string>
#include <unordered_set>
#include <vector>
#include <iterator>
#include <algorithm>
using namespace std;

void day1part2_withIterators()
{
	ifstream inFile("input.txt");
	vector<int> numbers;
	numbers.reserve(1000);
	istream_iterator<int> eos;              // end-of-stream iterator
	istream_iterator<int> iit(inFile);
	copy(iit, eos, back_inserter(numbers));
	int total = 0;
	unordered_set<int> answerFinder{ total };
	while (true)
	{
		for (auto number:numbers)
		{
			total += number;
			const auto [_, isInserted] = answerFinder.insert(total); // wow! structured bindings, boo! no std:ignore anymore
			if (!isInserted)
			{
				cout << total << endl;
				return;
			}
		}
	}
}

void day1part2()
{
	ifstream inFile("input.txt");
	int total = 0;
	int number;
	unordered_set<int> answerFinder{ total };
	while (true)
	{
		while (inFile >> number)
		{
			total += number;
			const auto[_, isInserted] = answerFinder.insert(total); // wow! structured bindings, boo! no std:ignore anymore
			if (!isInserted)
			{
				cout << total << endl;
				return;
			}
		}
		inFile.clear();
		inFile.seekg(0, ios::beg);
	}
}

void day1part1()
{
	ifstream inFile("input.txt");
	int total = 0;
	int number;
	while (inFile >> number)
	{
		total += number;
	}
	cout << total << endl;
}

int main()
{
	// todo experiment with timers
	//day1part1();
	//day1part2();
	day1part2_withIterators();
}

