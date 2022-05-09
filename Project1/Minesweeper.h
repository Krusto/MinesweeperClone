#pragma once
#include "Map.h"

namespace Minesweeper {
	class Game {
	public:
		Game(uint32_t size = 16) :m_Map(size) {}
		void Init();
		void Update();
	private:
		Map m_Map;
		Point m_SelectedPoint{};
		bool m_IsGameover{};
		uint32_t m_MovesLeft{};
		bool m_IsFirstMove{true};
	};
}