// Adv3.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>

#ifdef _WIN32
#include <cstdlib>
#endif // _WIN32

enum class Dirs { UP, DOWN, RIGHT, LEFT};

int main()
{
	int input = 325489;
	int x = 0, y = 0;
	int lastsquared = 1;
	Dirs currentDir = Dirs::RIGHT;
	bool nowup = true;
	int i = 1;

	input = 1024;

	while (i < input)
	{
		if (i == (lastsquared * lastsquared))
		{
			if (nowup)
			{
				currentDir = Dirs::UP;
				x += 1;
			}
			else {
				currentDir = Dirs::DOWN;
				x -= 1;
			}
			nowup = !nowup;
			++lastsquared;
			++i;
		}

		int stepsRem = (lastsquared - 1);

		if (input - (i + stepsRem) < 0)
		{
			stepsRem = input - i;
		}

		switch (currentDir)
		{
		case Dirs::RIGHT:
			x += stepsRem;
			i += stepsRem;
			currentDir = Dirs::UP;
			break;
		case Dirs::LEFT:
			x -= stepsRem;
			i += stepsRem;
			currentDir = Dirs::DOWN;
			break;
		case Dirs::UP:
			y += stepsRem;
			i += stepsRem;
			currentDir = Dirs::LEFT;
			break;
		case Dirs::DOWN:
			y -= stepsRem;
			i += stepsRem;
			currentDir = Dirs::RIGHT;
			break;
		}

	}

	std::cout << (x<0?x*(-1) : x) + (y<0 ? y * (-1) : y) << "("<<x<<", "<<y<<")\n";

#ifdef _WIN32
	system("PAUSE");
#endif // _WIN32

    return 0;
}

