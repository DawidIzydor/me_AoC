// day5.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#ifdef _WIN32
#include <cstdlib>
#endif // _WIN32

// changes string into int
// if there is non-numeric character
// then returns 0
// from day2
int stringToInt(std::string& input)
{
	int ret = 0;
	bool negative = input[0] == '-';

	for (int i = input.length() - 1; i >= (negative ? 1:0); --i)
	{
		int temp = input[i] - '0';
		if (temp >= 0 && temp <= 9)
		{
			ret += temp * pow(10, input.length() - i - 1);
		}
		else {
			return 0;
		}
	}
	if (negative)
	{
		ret *= -1;
	}
	return ret;
}

int main()
{

	std::ifstream input;
	input.open("input.txt");

	std::vector<int> intsVec;
	std::string tempStr;

	while (!input.eof())
	{
		std::getline(input, tempStr);
		intsVec.push_back(stringToInt(tempStr));
	}
	input.close();

	// for part 2
	// copy of the init values
	std::vector<int> intsVec2(intsVec);
	
	int steps = 0;
	for (int current = 0; current < intsVec.size(); steps++)
	{
		current += intsVec.at(current)++;
	}

	std::cout << steps << "\n";

	// part 2
	steps = 0;
	for (int current = 0; current < intsVec2.size(); steps++)
	{
		// wee need this as reference to make possible to change value
		auto& temp = intsVec2.at(current);
		current += temp;
		if (temp >= 3)
		{
			temp--;
		}
		else {
			temp++;
		}
	}
	std::cout << steps << "\n";

#ifdef _WIN32
	system("PAUSE");
#endif // _WIN32
    return 0;
}

