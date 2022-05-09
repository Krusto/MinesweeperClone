﻿#pragma once
#include <cstdint>
#include <cmath>
namespace Minesweeper {
	class Point {
	public:
		Point() = default;
		Point(float x, float y) : x(x), y(y) {}
		Point(const Point&) = default;

		Point& operator=(const Point& other) = default;
		bool operator==(const Point& rhs) {
			return (this->x == rhs.x && this->y == rhs.y);
		}
		Point& operator+=(const Point& rhs)
		{
			this->x += rhs.x;
			this->y += rhs.y;
			return *this;
		}
		Point& operator-=(const Point& rhs)
		{
			this->x -= rhs.x;
			this->y -= rhs.y;
			return *this;
		}
		bool operator!=(const Point& rhs)
		{
			return !(*this==rhs);
		}
		Point operator+(const Point& rhs)
		{
			float x = this->x + rhs.x;
			float y = this->y + rhs.y;
			return { x,y };
		}
		Point& operator*(float rhs) {
			this->x *= rhs;
			this->y *= rhs;
			return *this;
		}
		Point GetTrunc() { return { trunc(floor(x)),trunc(floor(y)) }; };
		float x{};
		float y{};
	};

}