// adv4.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>

#ifdef _WIN32
#include <cstdlib>
#endif


int main()
{
	std::ifstream input;
	input.open("input.txt");
	std::string line;
	
	int res = 0;
	
	while (!input.eof())
	{
		std::getline(input, line);
		std::unordered_map<std::string, int> map;
		std::string word;
		for (auto i : line)
		{
			if (i != ' ')
			{
				word += i;
			}
			else {
				++map[word];
				word = "";
			}
		}
		++map[word];

		bool isok = true;

		for (auto i : map)
		{
			if (i.second > 1)
			{
				isok = false;
				break;
			}
		}

		if (isok)

		{
			++res;
		}
	}

	input.close();
	std::cout << res << "\n";

#ifdef _WIN32
	system("PAUSE");
#endif // _WIN32
    return 0;
}

