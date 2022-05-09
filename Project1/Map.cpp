#include "Map.h"
#include <iostream>
#include <Windows.h>
#include "WindowsFunctions.h"
#include <algorithm>
#include <random>
namespace Minesweeper {
	Map::Map(uint32_t size)
	{
		m_Data.resize(size);
		std::for_each(m_Data.begin(), m_Data.end(), [&](std::vector<char>& el) {
			el.resize(size);
			});
		m_MineData.resize(size);
		std::for_each(m_MineData.begin(), m_MineData.end(), [&](std::vector<char>& el) {
			el.resize(size);
			});
		
		Fill('#');

		m_Size = size;
	}

	void Map::GenerateMines()
	{
		std::random_device r;
		std::mt19937 e1(r());
		std::uniform_int_distribution<int> uniform_dist(0,m_Size*m_Size);

		std::vector<bool> mark(m_Size * m_Size,false);

		uint32_t numMines = 40;
		for (int i = 0; i < numMines; )
		{
			int random = uniform_dist(e1);
			int x = (float)random / (float)m_Size;
			int y = random % m_Size;

			// Add the mine if no mine is placed at this
			// position on the board
			if (mark[random] == false)
			{
				m_MineData[x][y] = '*';
				mark[random] = true;
				i++;
			}
		}
	}
	
	const void Map::DrawMines() const
	{
		HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
		for (size_t x = 0; x < m_Size; x++)
		{
			for (size_t y = 0; y < m_Size; y++)
			{
				SetConsoleTextAttribute(out, 15);
				if (m_MineData[x][y] == '*') {
					std::cout << m_MineData[x][y];
				}
				else {
					std::cout<<'-';
				}

			}
			std::cout << '\n';
		}
	}

	const void Map::Draw() const{
		HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
		for (size_t x = 0; x < m_Size; x++)
		{
			for (size_t y = 0; y < m_Size; y++)
			{
				std::cout << m_Data[x][y];	
			}
			std::cout << '\n';
		}
	}

	
	void Map::Fill(int8_t symbol)
	{
		for (size_t x = 0; x < m_Size; x++)
		{
			for (size_t y = 0; y < m_Size; y++)
			{
				m_Data[x][y] = symbol;
				m_MineData[x][y] = ' ';
			}
		}
	}

	bool Map::ProcessClick(Point position, int* movesLeft)
	{
		if (m_Data[position.x][position.y] != '#')
			return false;
		
		if (IsValid(position)) {
			int8_t tile = Get(position);

			if (tile == '*') {
				return true;
			}
			else {
				auto count = CountAdjacentMines(position);
				(*movesLeft) = (*movesLeft)-1;

				m_Data[position.x][position.y] = count + '0';
				
				if (!count) {
					Point neighbours[8] = { Point(-1,-1),
											Point(-1,0),
											Point(-1,1),
											Point(0,-1),
											Point(0,1),
											Point(1,-1),
											Point(1,0),
											Point(1,1) };

					for (size_t i = 0; i < 8; i++)
					{
						Point newPos = position + neighbours[i];
						if (IsValid(newPos))
							if (!IsMine(newPos)) {
								ProcessClick(newPos, movesLeft);
							}
					}
				}
				return false;
			}
		}
	}

	uint32_t Map::CountAdjacentMines(Point position)
	{
		uint32_t count{};
		Point neighbours[8] = { Point(-1,0),
										Point(1,0),
										Point(0,1),
										Point(0,-1),
										Point(-1,1),
										Point(-1,-1),
										Point(1,1),
										Point(1,-1) };

		for (size_t i = 0; i < 8; i++)
		{
			Point newPos = position + neighbours[i];
			if (IsValid(newPos))
				if (IsMine(newPos))
					count++;
		}
		return count;
	}
	
}