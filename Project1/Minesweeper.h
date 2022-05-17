#pragma once
#include "Map.h" // библиотека за картата

namespace Minesweeper {
	class Game { // обект който е нашата игра
	public:
		Game(uint32_t size = 16) :m_Map(size) {} // конструктор на играта който задава размер на картата
		void Init(); // функция която инициализира играта
		void Update(); // функция която ъпдейтва играта
		bool IsReadyToExit() const {return m_Exit;} // функция която връща дали искаме да излезнем от играта
	private:
		Map m_Map; // променливата която е нашата карта
		Point m_SelectedPoint{}; // избрана точка от потребителят
		bool m_IsGameover{}; // променлива която връща дали сме умрели
		int m_MovesLeft{}; // променлива която държи колко клетки остават за отваряне
		bool m_IsFirstMove{true}; // променлива която се използва за проверка дали е първият ход
		uint32_t m_Score{}; // променлива за точките
		bool m_Exit{}; // флаг който казва дали трябва да излезнем
	};
}
