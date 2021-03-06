// day6.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <limits>

#ifdef _WIN32
#include <cstdlib>
#endif // _WIN32

// get index of the biggest number in vector
int getBiggestIndex(std::vector<int>& vec)
{
	// we could also use value = -1
	// as each number in vec is > 0
	// (from definition is number of blocks and there
	// cannot be a negative number of blocks)
	// but I like std::numeric_limits
	// its sexy
	int value = std::numeric_limits<int>::min();
	int ret = 0;

	int index = 0;
	for (auto a : vec)
	{
		if (a > value)
		{
			value = a;
			ret = index;
		}
		++index;
	}

	return ret;
}

int main()
{
	// changeg \t to ,
	// same can be done with a simple loop and stringToInt function
	// see day4 for more info
	std::vector<int> input{ 4,1,15,12,0,9,9,5,5,8,7,3,14,5,12,3 };
	std::map<std::vector<int>, int> usedStates{  };

	// count of moves
	int moves = 0;
	do
	{
		// we add input to a map
		// because std::map::find function is O(log)
		// and thats rather good
		// for part 2 we set the int as moves
		// it makes us a 'database' where
		// each used vector has an unique id
		// as the moves ascends after each iteration
		// the answer becomes a simple difference
		// of moves and found input->id
		usedStates[input] = moves;

		// index - where we start
		int index = getBiggestIndex(input);
		// a - how many steps we have to take
		int a = input.at(index);
		// after taking the steps we set the base to 0
		input.at(index) = 0;
		for (; a > 0; --a)
		{
			++index;
			if (index > input.size() - 1)
			{
				index = 0;
			}
			++input.at(index);
		}

		++moves;

	} while (usedStates.find(input) == usedStates.end());

	std::cout << moves << "\n";

	// part 2
	// The shortest part in calendar I think
	std::cout << moves - usedStates.find(input)->second << "\n";

#ifdef _WIN32
	system("PAUSE");
#endif // _WIN32
	return 0;
}

