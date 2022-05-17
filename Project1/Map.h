#pragma once
#include <cstdint>  // библиотека в която се намира uint8_t и uint32_t
#include <string>   // библиотека за текст
#include "Point.h"  // библиотека където е дефинирана структурата точка
#include <vector>   // билиботека за низове от данни

namespace Minesweeper { // в този namespace ни се намират всички класове и функции за играта

	class Map { // обект Map, който е картата на играта
	public:
		Map(uint32_t size); // конструктор на обекта с параметър size, който задава големина на картата

		void Set(Point pos, int8_t value) { m_MineData[(int)pos.x][(int)pos.y] = value; } // функция която замества дадена точка от картата с value
		void SetMine(Point pos) { m_MineData[(int)pos.x][(int)pos.y] = '*'; } // функция която слага мина в дадена точка от картата
		void GenerateMines(); // функция за генериране на мини

		int8_t Get(Point pos) const {  // функция за взимане на стойността на клетка в картата
			if (IsValid(pos))  // проверяваме дали точката се намира в картата
				return m_MineData[(int)pos.x][(int)pos.y]; // връщаме стойността на клетката в тази точка
		}

		bool IsValid(Point pos) { return (pos.y < m_Size && pos.x < m_Size && pos.x >= 0 && pos.y >= 0); } // функция която проверява дали точката се намира в картата
		bool IsValid(Point pos) const { return (pos.y < m_Size && pos.x < m_Size && pos.x >= 0 && pos.y >= 0); }// функция която проверява дали точката се намира в картата

		auto& data() { return m_Data; } // функция която връща низ от данни за картата, която се показва на екрана
		auto& mine_data() { return m_MineData;} // функция която връща низ от данни, за това къде има мини

		auto GetSize() const { return m_Size; }; // функция която връща големината на картата

		const void DrawMines() const; // функция която показва къде има мини
		const void Draw() const; // функция която рисува картата със разкритите пространства
		void Fill(int8_t symbol); // функция която запълва картата със value

		bool ProcessClick(Point position,int* movesLeft); // функция която взима точка и я замества с номер на мините около нея,
                                                          // и замества околните клетки които не са мина с празно пространство
		bool IsMine(Point position) const { return m_MineData[position.x][position.y] == '*'; } // функция която проверява дали е настъпена мина
		uint32_t CountAdjacentMines(Point position); // функция която връща броя на мините около точка
	private:
		std::vector<std::vector<char>> m_MineData; // 2D низ от символи с информация къде се намират мините
		std::vector<std::vector<char>> m_Data; // 2D низ от символи с информация която се показва на играча

		uint32_t m_Size{}; // големина на картата
	};

}
