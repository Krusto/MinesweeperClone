#pragma once
#include <cmath> // библиотека която включва математически функции
namespace Minesweeper {
	class Point { // клас точка която има х,у
	public:
		Point() = default; // конструктор който се извиква за подразбиране
		Point(float x, float y) : x(x), y(y) {} // конструктор който приема х,y
		Point(const Point&) = default; // конструктор който взима друга точка и копира нейните x,y

		Point& operator=(const Point& other) = default; // оператор който копира x,y на друга точка
		bool operator==(const Point& rhs) { // оператор който сравнява тази точка с друга точка
			return (this->x == rhs.x && this->y == rhs.y);
		}
		Point& operator+=(const Point& rhs) // оператор който инкрементира x,y на тази точка с друга точка
		{
			this->x += rhs.x;
			this->y += rhs.y;
			return *this;
		}
		Point& operator-=(const Point& rhs) // оператор който декрементира x,y на тази точка с друга точка
		{
			this->x -= rhs.x;
			this->y -= rhs.y;
			return *this;
		}
		bool operator!=(const Point& rhs) // опратор който сравнява дали не са равни точка с друга точка
		{
			return !(*this==rhs);
		}
		Point operator+(const Point& rhs) // оператор който събира две точки и връща техният сбор
		{
			float x = this->x + rhs.x;
			float y = this->y + rhs.y;
			return { x,y };
		}
		Point& operator*(float rhs) { // опратор който умножава тази точка с друга точка
			this->x *= rhs;
			this->y *= rhs;
			return *this;
		}
		Point GetTrunc() { return { trunc(floor(x)),trunc(floor(y)) }; }; // функция която връща x,y без числата след десетична запетая
		float x{};
		float y{};
	};

}
