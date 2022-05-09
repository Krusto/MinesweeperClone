#pragma once
#include <cstdint>
#include <string>
#include "Point.h"
#include <vector>

namespace Minesweeper {

	class Map {
	public:
		Map(uint32_t size);

		void Set(Point pos, int8_t value) { m_MineData[(int)pos.x][(int)pos.y] = value; }
		void SetMine(Point pos) { m_MineData[(int)pos.x][(int)pos.y] = '*'; }
		void GenerateMines();

		int8_t Get(Point pos) const { 
			if (IsValid(pos)) 
				return m_MineData[(int)pos.x][(int)pos.y];
		}

		bool IsValid(Point pos) { return (pos.y < m_Size && pos.x < m_Size && pos.x >= 0 && pos.y >= 0); }
		bool IsValid(Point pos) const { return (pos.y < m_Size && pos.x < m_Size && pos.x >= 0 && pos.y >= 0); }
		
		auto& data() { return m_Data; }
		auto& mine_data() { return m_MineData; }

		auto GetSize() const { return m_Size; };

		const void DrawMines() const;
		const void Draw() const;
		void Fill(int8_t symbol);

		bool ProcessClick(Point position,int* movesLeft);
		bool IsMine(Point position) const { return m_MineData[position.x][position.y] == '*'; }
		uint32_t CountAdjacentMines(Point position);
	private:
		std::vector<std::vector<char>> m_MineData;
		std::vector<std::vector<char>> m_Data;

		uint32_t m_Size{};
	};

}