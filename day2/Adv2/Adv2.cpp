// Adv2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
#include <string>
#include <limits>
#include <vector>

#ifdef _WIN32
#include <cstdlib>
#endif // _WIN32

// to distinguish how we split the table into pieces
#define NEWLINE 'n'
#define SPACETAB '\t'


// changes string into int
// if there is non-numeric character
// then returns 0
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
	// the only thing i did to input was to change \n into n
	// it could be still done with reading from file
	// then you'd have to change one if
	// but I'm lazy and this will do the job
	std::string input = "1136	1129	184	452	788	1215	355	1109	224	1358	1278	176	1302	186	128	1148n242	53	252	62	40	55	265	283	38	157	259	226	322	48	324	299n2330	448	268	2703	1695	2010	3930	3923	179	3607	217	3632	1252	231	286	3689n89	92	903	156	924	364	80	992	599	998	751	827	110	969	979	734n100	304	797	81	249	1050	90	127	675	1038	154	715	79	1116	723	990n1377	353	3635	99	118	1030	3186	3385	1921	2821	492	3082	2295	139	125	2819n3102	213	2462	116	701	2985	265	165	248	680	3147	1362	1026	1447	106	2769n5294	295	6266	3966	2549	701	2581	6418	5617	292	5835	209	2109	3211	241	5753n158	955	995	51	89	875	38	793	969	63	440	202	245	58	965	74n62	47	1268	553	45	60	650	1247	1140	776	1286	200	604	399	42	572n267	395	171	261	79	66	428	371	257	284	65	25	374	70	389	51n3162	3236	1598	4680	2258	563	1389	3313	501	230	195	4107	224	225	4242	4581n807	918	51	1055	732	518	826	806	58	394	632	36	53	119	667	60n839	253	1680	108	349	1603	1724	172	140	167	181	38	1758	1577	748	1011n1165	1251	702	282	1178	834	211	1298	382	1339	67	914	1273	76	81	71n6151	5857	4865	437	6210	237	37	410	544	214	233	6532	2114	207	5643	6852";

	std::vector<std::vector<int>> inputTab;
	int i = 0;

	int res = 0;

	// PART 1

	while (i < input.length())
	{
		//std::vector<int> tempVec;
		int linemin = std::numeric_limits<int>::max();
		int linemax = 0;

		std::vector<int> tempvect; // for part 2

		// change n to \n if read from file
		while (i < input.length() && input[i] != NEWLINE)
		{

			std::string temp = "";

			while (i < input.length() && input[i] != SPACETAB && input[i] != NEWLINE)
			{
				temp += input[i];
				++i;
			}

			int tempint = stringToInt(temp);

			tempvect.push_back(tempint); // for part 2

			if (tempint < linemin)
			{
				linemin = tempint;
			}

			if (tempint > linemax)
			{
				linemax = tempint;
			}

			if (input[i] != NEWLINE)
			{
				++i;
			}
		}

		inputTab.push_back(tempvect); // for part 2

		res += linemax - linemin;

		++i;

	}

	std::cout << res << "\n";

	// part 2
	// to ease part 2 the numbers are put into vector in part one
	res = 0;
	for (auto& a : inputTab)
	{
		for (int i = 0; i < a.size(); ++i)
		{
			for (int j = 0; j < a.size(); ++j)
			{
				if (i != j) {
					if (a.at(i) % a.at(j) == 0)
					{
						res += a.at(i) / a.at(j);
					}
				}
			}
		}
	}

	std::cout << res<<"\n";

#ifdef _WIN32
	system("PAUSE");
#endif // _WIN32


    return 0;
}

