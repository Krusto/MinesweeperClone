#include "Math.h"
float GetDistance(Minesweeper::Point p1, Minesweeper::Point p2)
{
	return sqrt(pow(p2.x - p1.x, 2) +
		pow(p2.y - p1.y, 2) * 1.0);
}