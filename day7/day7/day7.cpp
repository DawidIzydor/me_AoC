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

struct MapStruct;

std::map<std::string, MapStruct> strMap;

// A struct to contain data for each leaf
struct MapStruct
{
	// name of current leaf, the same as strMap.first
	std::string name;

	// children of links
	std::vector<std::string> childrens;

	// parrent of link
	// the main leaf will have no parrent
	std::string parrent = "";

	// weight of leaf
	int weight;

	// for part 2
	// returns total weight of object
	// and all Childrens
	int getTotalWeight()
	{
		return weight + getChildrensWeignt();
	}

	// for part 2
	// returns total weight of Childrens
	int getChildrensWeignt()
	{
		int childrensWeight = 0;
		for (auto i : childrens)
		{
			childrensWeight += strMap[i].getTotalWeight();
		}
		return childrensWeight;
	}

	// for part 2
	// returns true if this leaf is balanced or has no children
	bool isBalanced()
	{
		if (childrens.size() == 0)
		{
			return true;
		}
		else {
			for (int i = 0; i < childrens.size(); ++i)
			{
				if (strMap[childrens.at(i)].isBalanced()) {

					int ithWeight = strMap[childrens.at(i)].getTotalWeight();

					for (int j = i + 1; j < childrens.size(); ++j)
					{
						if (strMap[childrens.at(j)].getTotalWeight() != ithWeight)
						{
							return false;
						}
					}
				}
				else {
					return false;
				}
			}
			return true;
		}
	}

	// for part 2
	// gets the master leaf of unbalanced 
	std::string getUnbalancedMaster()
	{
		if (childrens.size() == 0)
		{
			return parrent;
		}

		for (int i = 0; i < childrens.size(); ++i)
		{
			if (strMap[childrens.at(i)].isBalanced()) {

				int ithWeight = strMap[childrens.at(i)].getTotalWeight();

				for (int j = i + 1; j < childrens.size(); ++j)
				{
					int jthWeight = strMap[childrens.at(j)].getTotalWeight();

					if (jthWeight != ithWeight)
					{
						return strMap[childrens.at((ithWeight > jthWeight ? i : j))].getUnbalancedMaster();
					}
				}
			}
		}
		return parrent;
	}
};

int main()
{
	std::ifstream inputFile;

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
			ref.name = words.at(0);
			// second is weight, we delete the ()
			words.at(1).erase(0, 1);
			words.at(1).erase(words.at(1).size() - 1, 1);
			ref.weight = stringToInt(words.at(1));

			for (int i = 3; i < words.size(); ++i)
			{
				if (words.at(i)[words.at(i).size() - 1] == ',')
				{
					words.at(i).erase(words.at(i).size() - 1);
				}
				strMap[words.at(i)].parrent = words.at(0);
				strMap[words.at(0)].childrens.push_back(words.at(i));
			}

		}
	}
	inputFile.close();

	for (auto i : strMap)
	{
		if (i.second.parrent == "")
		{
			std::cout << i.first << "\n";
		}
	}

	// part 2

	// first we search for the unbalanced's id
	// There should be only one but this can be easily rearranged
	// to find any number of unbalanced
	// only problem would be that this one might be anywhere in the tree
	// we only care about it's children here but
	// if the parrent of first found unbalanced is in map after it's children
	// that they will finally point to the same leaf
	// anyway as we have only 1 unbalanced we do not have to care about it
	std::string unbalanced;
	for (auto i : strMap)
	{
		if (!i.second.isBalanced())
		{
			unbalanced = i.first;
			break;
		}
	}

	// if we found any unbalanced
	if (unbalanced != "")
	{
		// needed to check every weight 
		auto& childrensOfUnbalanced = strMap[strMap[unbalanced].getUnbalancedMaster()].childrens;

		// the heaviest weight
		int biggest = 0;

		// the least heavy weight
		int smallest = std::numeric_limits<int>::max();

		// the name of the heaviest
		// this is need to check the actual weight of element, not it's total
		std::string biggestname;

		for (auto i : childrensOfUnbalanced)
		{
			auto temp = strMap[i].getTotalWeight();
			if (temp < smallest)
			{
				smallest = temp;
			}
			if (temp > biggest)
			{
				biggest = temp;
				biggestname = i;
			}
		}

		// as we have only 1 unbalanced this last line is easy, we just need to make a difference
		// between the weight and how much we are over that weight
		std::cout << strMap[biggestname].weight - (biggest - smallest)<<"\n";
	}


#ifdef _WIN32
	system("PAUSE");
#endif // _WIN32
    return 0;
}

