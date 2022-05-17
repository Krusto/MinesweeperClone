#include "Minesweeper.h"
#include <Windows.h> // библиотека използвана за манипулиране на конзолата
#include "WindowsFunctions.h"//библиотека в която са дефинирани функции за манипулиране на конзолата
#include <iostream> // библиотека за input/output в конзолата
void Minesweeper::Game::Init()
{
	m_Map.Fill('#'); // запълваме картата #
	m_Map.GenerateMines(); // генерираме мини на картата
	m_MovesLeft = m_Map.GetSize() * m_Map.GetSize() - 40; // изчисляваме броят клетки без мини
}

void Minesweeper::Game::Update()
{
	ClearScreen(); // изчистваме екрана
	if (!m_IsGameover && m_MovesLeft > 0) { // поверяваме дали сме умрели и дали имаме повече от 0 хода
		m_Map.Draw(); // рисуваме картата

		std::cout << "Score : "<<m_Score<<"\nPlease enter coordinate : "; // показваме точките и чакаме вход от потребителят

		std::cin >> m_SelectedPoint.x >> m_SelectedPoint.y; // взимаме вход от потребителят

		if (!m_Map.IsValid(m_SelectedPoint)) // проверяваме дали тази точка не е в картата
			return; // излизаме защото точката е невалидна

		if (m_Map.IsMine(m_SelectedPoint) && !m_IsFirstMove) // проверяваме дали сме настъпили мина и дали не е първият ход
			m_IsGameover = true; // умира играчът защото е настъпил мина

		if (m_IsFirstMove && m_Map.IsMine(m_SelectedPoint)) { // проверяваме дали е първи ход и е настъпена мина
			m_Map.Set(m_SelectedPoint, ' '); // понеже е първи ход, премахваме мината
		}

		uint32_t currentMovesCount = m_MovesLeft; // взимаме броят ходове които остават
		m_Map.ProcessClick(m_SelectedPoint,&m_MovesLeft); // отваряме всички клетки които са свободни
		m_Score += currentMovesCount - m_MovesLeft; // взимаме разликата от предишният брой ходове и сегашния и променяме точките
        m_IsFirstMove = false; // задаваме че вече не е първи ход
	}
	else if (m_Score >= m_Map.GetSize() * m_Map.GetSize() - 40) { // иначе ако сме събрали максималният брой точки
		ClearScreen(); // изчистваме екрана
		m_Map.DrawMines(); // показваме къде са били мините
		std::cout << "You Win!\n"; // принтираме текст с печелившо съобщение
		std::cout << "Score: " << m_Score << '\n'; // принтираме точките
		std::cin.ignore(); // изчакваме вход от потребителят
		m_Exit = true; // казваме че искаме да излезнем
	}
	else { // иначе
		m_Map.DrawMines(); // рисуваме мините
		std::cout << "Game Over\n"; // принтираме съощение че е загубил играта
		std::cout << "Score: " << m_Score << '\n'; // принтираме точките
		std::cin.ignore(); // изчакваме вход от потребителят
		m_Exit = true; // казваме че искаме да излезнем
	}
}
