// day7.cpp : Defines the entry point for the console application.
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

struct MapStruct
{
	std::vector<std::string> linkedStrs;
	std::string linksTo;
	int weight;
};

int main()
{
	std::ifstream inputFile;
	std::map<std::string, MapStruct> strMap;

	inputFile.open("input.txt");
	//inputFile.open("testinput.txt");

	std::string lineStr;
	while (!inputFile.eof())
	{
		std::getline(inputFile, lineStr);

		if (lineStr != "") {

			std::vector<std::string> words;
			std::string tempStr;

			for (int i = 0; i < lineStr.size(); ++i)
			{
				if (lineStr[i] != ' ')
				{
					tempStr += lineStr[i];
				}
				else {
					words.push_back(tempStr);
					tempStr = "";
				}
			}
			words.push_back(tempStr);

			// first in words vector is the word we are working on
			auto& ref = strMap[words.at(0)];
			// second is weight, we delete the ()
			words.at(1).erase(0, 1);
			words.at(1).erase(words.at(1).size() - 1, 1);

			for (int i = 3; i < words.size(); ++i)
			{
				if (words.at(i)[words.at(i).size() - 1] == ',')
				{
					words.at(i).erase(words.at(i).size() - 1);
				}
				strMap[words.at(i)].linksTo = words.at(0);
				strMap[words.at(0)].linkedStrs.push_back(words.at(i));
			}

		}
	}
	inputFile.close();

	for (auto i : strMap)
	{
		if (i.second.linksTo == "")
		{
			std::cout << i.first<<"\n";
		}
	}



#ifdef _WIN32
	system("PAUSE");
#endif // _WIN32
    return 0;
}

