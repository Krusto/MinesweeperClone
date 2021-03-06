#include "Map.h"
#include <iostream>// библиотека за input/output в конзолата
#include <Windows.h>  // библиотека използвана за манипулиране на конзолата
#include "WindowsFunctions.h" //библиотека в която са дефинирани функции за манипулиране на конзолата
#include <algorithm> // библиотека за алгоритми
#include <random> // библиотека за произволни числа
namespace Minesweeper {
	Map::Map(uint32_t size) // конструктор на клас Карта
	{
		m_Data.resize(size); // казваме на низа да има size редове
		std::for_each(m_Data.begin(), m_Data.end(), [&](std::vector<char>& el) { // за всеки ред взимаме низ от символи
			el.resize(size); // казвваме колко колони искаме да има редът
			});

		m_MineData.resize(size); // казваме на низа да има size редове
		std::for_each(m_MineData.begin(), m_MineData.end(), [&](std::vector<char>& el) { // за всеки ред взимаме низ от символи
			el.resize(size); // казвваме колко колони искаме да има редът
			});

		Fill('#'); // запълваме картата която вижда играчът с #

		m_Size = size; // задаваме размерът на картата да е равен на size
	}

	void Map::GenerateMines()
	{
		std::random_device r; // използва се за да вземем seed за функцията която генерира числа
		std::mt19937 e1(r()); // генератор на произволни числа който приема сийд r
		std::uniform_int_distribution<int> uniform_dist(0,m_Size*m_Size); //  тук казваме че искаме числа
                                                                          // които са от 0 до броят на клетките на картата

		std::vector<bool> mark(m_Size * m_Size,false); // низ в който записваме дали тази клетка вече е заета

		uint32_t numMines = 40; // променлива която казва колко мини да се генерират
		for (int i = 0; i < numMines; ) // изпълнява се докато i не стане равно на максималният брой мини
		{
			int random = uniform_dist(e1); // взимаме някакво произволно число
			int x = (float)random / (float)m_Size; // това произволно число го делим
                                                   //на големината на картата и взимаме
                                                   //числата преди десетичната запетая
			int y = random % m_Size; // тук взимаме остатъкът на делението

			if (mark[random] == false) // проверяваме дали има мина, ако няма добавяме
			{
				m_MineData[x][y] = '*'; // слагаме мина в точка x,y
				mark[random] = true; // казваме че тази клетка е заета
				i++; // i го увеличаваме с едно, защото имаме 1 мина повече
			}
		}
	}

	const void Map::DrawMines() const // функция която рисува мините
	{
		HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE); // взимаме сегашната конзола
		for (size_t x = 0; x < m_Size; x++) // минаваме през всяко х на картата
		{
			for (size_t y = 0; y < m_Size; y++) // минаваме през всяко у на картата
			{
				SetConsoleTextAttribute(out, 15); // задаваме цветът в който се рисува да е 15
				if (m_MineData[x][y] == '*') { // ако в тази точка има мина рисуваме мина
					std::cout << '*'; // рисуваме мина на конзолата
				}
				else { // ако не е мина рисуваме празно пространство
					std::cout<<'-';
				}

			}
			std::cout << '\n'; // минаваме на следващият ред
		}
	}

	const void Map::Draw() const{ // рисуваме картата на потребителят
		for (size_t x = 0; x < m_Size; x++) // минаваме през всяко х на картата
		{
			for (size_t y = 0; y < m_Size; y++) // минаваме през всяко у на картата
			{
				std::cout << m_Data[x][y]; // рисуваме информацията в клетката
			}
			std::cout << '\n'; // минаваме на слеващ ред
		}
	}


	void Map::Fill(int8_t symbol) // функция която запълва клетките с някакъв symbol
	{
		for (size_t x = 0; x < m_Size; x++) // минаваме през всяко х на картата
		{
			for (size_t y = 0; y < m_Size; y++) // минаваме през всяко у на картата
			{
				m_Data[x][y] = symbol; // заместваме точка х,у на картата с symbol
				m_MineData[x][y] = ' '; // заместваме точка х,у на низа с мини да е празно
			}
		}
	}

	bool Map::ProcessClick(Point position, int* movesLeft) // функция която взима точка и я замества с номер на мините около нея,
    {                                                      // и замества околните клетки които не са мина с празно пространство

		if (m_Data[position.x][position.y] != '#') // проверяваме дали клетка в тази точка е празна
			return false; // понеже вече е разкрита клетката излизаме от функцията с резултат лъжа,
                          // защото не е мина

		if (IsValid(position)) { // проверяваме дали тази точка е в картата
			int8_t tile = Get(position); // взимаме стойността на клетката с тази точка

			if (tile == '*') { // проверяваме дали тази клетка е мина
				return true; // ако е мина връщаме истина защото сме я настъпили
			}
			else { // иначе ако не е мина
				auto count = CountAdjacentMines(position); // взимаме броят на мините около тази клетка
				(*movesLeft) = (*movesLeft)-1; // броят на възможните клетки за отваряне намаляме с 1,
                                               // защото сме я разкрили
                if(count != 0){ // проверяваме дали имаме повече от 0 мини около нас
                    m_Data[position.x][position.y] = count + '0'; // задаваме казваме на тази клетка да е равна на
                                                              // броят мини около нея
                }else{ // иначе
                    m_Data[position.x][position.y] = ' ';  // клетката става празна защото няма мини около нея
                }
				if (!count) { // ако броят мини е 0
					Point neighbours[8] = { Point(-1,-1),  // тук дефинираме позицията на всички
											Point(-1,0),   // точки релативно около нашата клетка
											Point(-1,1),
											Point(0,-1),
											Point(0,1),
											Point(1,-1),
											Point(1,0),
											Point(1,1) };

					for (size_t i = 0; i < 8; i++) // итерираме през всички съседни клетки
					{
						Point newPos = position + neighbours[i]; // изчисляваме абсолютната позиция на съседната клетка
						if (IsValid(newPos)) // проверяваме дали новата точка се намира в картата
							if (!IsMine(newPos)) { // проверяваме дали тази точка не е мина
								ProcessClick(newPos, movesLeft); // понеже не е мина извикваме рекурсивно сегашната функция отново
							}
					}
				}
				return false; // излиза функцията с резултат лъжа, защото не е настъпена мина
			}
		}
	}

	uint32_t Map::CountAdjacentMines(Point position) // функция която брои мините около точка
	{
		uint32_t count{}; // променлива която държи броят мини
		Point neighbours[8] = { Point(-1,0),// тук дефинираме позицията на всички
										Point(1,0),// точки релативно около нашата клетка
										Point(0,1),
										Point(0,-1),
										Point(-1,1),
										Point(-1,-1),
										Point(1,1),
										Point(1,-1) };

		for (size_t i = 0; i < 8; i++) // итерираме през всички съседни клетки
		{
			Point newPos = position + neighbours[i]; // изчисляваме абсолютната позиция на съседната клетка
			if (IsValid(newPos)) // проверяваме дали клетката се намира в картата
				if (IsMine(newPos)) // проверяваме дали е мина
					count++; // понеже е мина броят се увеличава с 1
		}
		return count; // връщаме резултат от функцията да бъде броят мини
	}

}
