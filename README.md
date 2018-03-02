# Advent of Code 2017 
Advent of code http://adventofcode.com/2017

## Content

Each folder contains full Visual Studio solution to each day

# Advent of Code
Advent of Code is a series of small programming puzzles for a variety of skill levels. They are self-contained and are just as appropriate for an expert who wants to stay sharp as they are for a beginner who is just learning to code. Each puzzle calls upon different skills and has two parts that build on a theme.
From reddit https://www.reddit.com/r/adventofcode/

# Useful functions

## ```stringToInt```
```c++
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
```

## ```hash<Point>()```
Hash for 2D Point struct  (see https://github.com/DawidIzydor/me_HashNrsOptimizer)
```c++
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

namespace std {

	template <>
	struct hash<Point2D>
	{
		size_t hash(const Point2D& k, int x, int y)
		{
			unsigned long int a = k.x * 5;
			unsigned long int b = k.y * 941 + std::numeric_limits<int>::max();
			if (k.x <= 0) {
				a = a << b;
			}
			if (k.y <= 0)
			{
				b = b << a << 1;
			}

			size_t res = a ^ b;

			return res;
		}
	};

}

```
