// Adv3.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
#include <unordered_map>

#ifdef _WIN32
#include <cstdlib>
#endif // _WIN32

enum class Dirs { UP, DOWN, RIGHT, LEFT};

// for Point 2
// the same can be achieved using arrays
// but Im ambitious
struct Point2D
{
	int x;
	int y;

	Point2D() = delete;

	Point2D(int _x, int _y) {
		x = _x;
		y = _y;
	}

	bool operator==(const Point2D& other) const
	{
		return (x == other.x && y == other.y);
	}
};

// for point 2
// needed for std::unordered_map
namespace std {

	template <>
	struct hash<Point2D>
	{
		size_t operator()(const Point2D& k) const
		{
			unsigned long int a = k.x;
			unsigned long int b = k.y + std::numeric_limits<int>::max();
			if (k.x <= 0) {
				a = a >> 1;
			}
			if (k.y <= 0)
			{
				b = b >> 1;
			}
			size_t res = a ^ b;

			return res;
		}
	};

}

int main()
{
    int input = 325489;
	int x = 0, y = 0;
	int lastsquared = 1;
	Dirs currentDir = Dirs::RIGHT;
	bool nowup = true;
	int i = 1;

	//input = 1024;

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


	// part 2
	i = 1;
	x = 0; y = 0;
	lastsquared = 1;
	currentDir = Dirs::RIGHT;
	nowup = true;
	std::unordered_map<Point2D, int> map;
	map[Point2D(0, 0)] = 1;
	int sumaround = 0;
	//input = 10;

	while (sumaround <= input)
	{
		sumaround = 0;
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
			sumaround = 0;
			for(int ai = -1; ai <= 1; ai++)
			{
				for (int aj = -1; aj <= 1; aj++)
				{
					sumaround += map[Point2D(x+ai, y+aj)];
				}

			}
			map[Point2D(x, y)] = sumaround;

			nowup = !nowup;
			++lastsquared;
			++i;
		}
		else {

			int rest = (lastsquared - 1);

			for (int k = 0; k < rest && sumaround <= input; ++k) {
				int stepsRem = 1;

				switch (currentDir)
				{
				case Dirs::RIGHT:
					x += stepsRem;
					i += stepsRem;
					break;
				case Dirs::LEFT:
					x -= stepsRem;
					i += stepsRem;
					break;
				case Dirs::UP:
					y += stepsRem;
					i += stepsRem;
					break;
				case Dirs::DOWN:
					y -= stepsRem;
					i += stepsRem;
					break;
				}

				sumaround = 0;
				for (int ai = -1; ai <= 1; ai++)
				{
					for (int aj = -1; aj <= 1; aj++)
					{
						sumaround += map[Point2D(x + ai, y + aj)];
					}

				}
				map[Point2D(x, y)] = sumaround;
			}


			switch (currentDir)
			{
			case Dirs::RIGHT:
				currentDir = Dirs::UP;
				break;
			case Dirs::LEFT:
				currentDir = Dirs::DOWN;
				break;
			case Dirs::UP:
				currentDir = Dirs::LEFT;
				break;
			case Dirs::DOWN:
				currentDir = Dirs::RIGHT;
				break;
			}

		}
	}

	std::cout << x << "," << y << ": " << sumaround << "\n";
#ifdef _WIN32
	system("PAUSE");
#endif // _WIN32

    return 0;
}

