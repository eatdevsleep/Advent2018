// Day1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <fstream>
#include <string>
#include <unordered_set>
using namespace std;

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
			const auto [_, isInserted] = answerFinder.insert(total); // wow! structured bindings
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
	//day1part1();
	day1part2();
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
