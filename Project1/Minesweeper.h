#pragma once
#include "Map.h"

namespace Minesweeper {
	class Game {
	public:
		Game(uint32_t size = 16) :m_Map(size) {}
		void Init();
		void Update();
		bool IsReadyToExit() const {return m_Exit;}
	private:
		Map m_Map;
		Point m_SelectedPoint{};
		bool m_IsGameover{};
		int m_MovesLeft{};
		bool m_IsFirstMove{true};
		uint32_t m_Score{};
		bool m_Exit{};
	};
}