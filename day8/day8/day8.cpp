// day8.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <limits>
#include <fstream>

#ifdef _WIN32
#include <cstdlib>
#endif // _WIN32

// changes string into int
// if there is non-numeric character
// then returns 0
int stringToInt(std::string& input)
{
	int ret = 0;
	bool negative = input[0] == '-';

	for (int i = input.length() - 1; i >= (negative ? 1 : 0); --i)
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

// function that takes a string and then
// splits it into pieces
// similar to PHP's explode() fucntion
std::vector<std::string> stringExplode(std::string& str, char what = ' ')
{
	std::vector<std::string> words;
	std::string tempStr;

	for (int i = 0; i < str.size(); ++i)
	{
		if (str[i] != what)
		{
			tempStr += str[i];
		}
		else {
			words.push_back(tempStr);
			tempStr = "";
		}
	}
	words.push_back(tempStr);

	return words;
}

int main()
{

	std::map < std::string, int> strMap;
	std::ifstream inputText;
	inputText.open("input.txt");
	//inputText.open("testinput.txt");
	std::string lineStr;

	//for part 2
	int biggest2 = std::numeric_limits<int>::min();

	while (!inputText.eof())
	{
		std::getline(inputText, lineStr);
		if (lineStr != "") {
			auto words = stringExplode(lineStr);

			bool isif = false;

			if (words.at(5) == ">")
			{
				if (strMap[words.at(4)] > stringToInt(words.at(6)))
				{
					isif = true;
				}
			}
			else if (words.at(5) == "<")
			{
				if (strMap[words.at(4)] < stringToInt(words.at(6)))
				{
					isif = true;
				}
			}
			else if (words.at(5) == ">=")
			{
				if (strMap[words.at(4)] >= stringToInt(words.at(6)))
				{
					isif = true;
				}
			}
			else if (words.at(5) == "<=")
			{
				if (strMap[words.at(4)] <= stringToInt(words.at(6)))
				{
					isif = true;
				}
			}
			else if (words.at(5) == "==")
			{
				if (strMap[words.at(4)] == stringToInt(words.at(6)))
				{
					isif = true;
				}
			}
			else if (words.at(5) == "!=")
			{
				if (strMap[words.at(4)] != stringToInt(words.at(6)))
				{
					isif = true;
				}
			}
			if (isif)
			{
				strMap[words.at(0)] += (words.at(1) == "dec" ? -1 : 1)*stringToInt(words.at(2));

				// for part 2
				if (strMap[words.at(0)] > biggest2)
				{
					biggest2 = strMap[words.at(0)];
				}
			}
		}

	}
	inputText.close();

	int biggest = std::numeric_limits<int>::min();

	for (auto el : strMap)
	{
		if (el.second > biggest)
		{
			biggest = el.second;
		}

	}
	std::cout << biggest << "\n";

	//part 2
	// second shortest part after day6
	std::cout << biggest2 << "\n";


#ifdef _WIN32
	system("PAUSE");
#endif // _WIN32
	return 0;
}
