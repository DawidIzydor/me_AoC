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

	// for part 2
	std::vector<std::unordered_map<std::string, int>> linesVec;

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

		// for part 2
		linesVec.push_back(map);
	}

	input.close();

	std::cout << res << "\n";

	// part 2

	int res2 = 0;

	// for every line in lines vector
	for (auto line : linesVec) {

		bool isGood = true;

		std::vector<std::unordered_map<char, int>> wordVec;

		// count how many times is used each char in each word
		for (auto word : line) {

			// if any word appears in a line twice
			// then the rearangement is trival
			if (word.second > 1)
			{
				isGood = false;
				break;
			}

			std::unordered_map<char, int> tempMap;
			for (auto chari : word.first)
			{
				++tempMap[chari];
			}
			wordVec.push_back(tempMap);
		}

		if (isGood) {

			// for each word in vector we have to compare each char
			// to each char in the other
			// at least we are comparing only numbers of occurences
			for (int k = 0; k < wordVec.size() && isGood; ++k)
			{
				for (int j = k + 1; j < wordVec.size() && isGood; ++j)
				{
					bool isDiff = false;

					for (auto ch : wordVec.at(k))
					{
						if (ch.second != wordVec.at(j)[ch.first])
						{
							isDiff = true;
							break;
						}
					}

					if (!isDiff)
					{
						// the same for had to be used twice
						// the alternative was to use something like
						// for (auto ch : wordVec.at((wordVec.at(j).size() > wordVec.at(k).size() ? j : k)))
						// and then in the if the oposite <
						// but i couldn't make it into working
						for (auto ch : wordVec.at(j))
						{
							if (ch.second != wordVec.at(k)[ch.first])
							{
								isDiff = true;
								break;
							}
						}

						// only if we have at least one difference then it's ok
						if (!isDiff) {
							isGood = false;
							break;
						}
					}
				}
			}

			if (isGood)
			{
				++res2;
			}
		}
	}

	std::cout << res2 << "\n";
#ifdef _WIN32
	system("PAUSE");
#endif // _WIN32
	return 0;
}