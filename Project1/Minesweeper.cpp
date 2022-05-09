#include "Minesweeper.h"
#include <Windows.h>
#include "WindowsFunctions.h"
#include <iostream>
void Minesweeper::Game::Init()
{
	m_Map.Fill('#');
	m_Map.GenerateMines();
	m_MovesLeft = m_Map.GetSize() * m_Map.GetSize() - 40;
}

void Minesweeper::Game::Update()
{
	ClearScreen();
	if (!m_IsGameover && m_MovesLeft > 0) {
		m_Map.Draw();

		std::cout << "Score : "<<m_Score<<"\nPlease enter coordinate : ";

		std::cin >> m_SelectedPoint.x >> m_SelectedPoint.y;

		if (!m_Map.IsValid(m_SelectedPoint))
			return;

		if (m_Map.IsMine(m_SelectedPoint) && !m_IsFirstMove) 
			m_IsGameover = true;

		if (m_IsFirstMove && m_Map.IsMine(m_SelectedPoint)) {
			m_Map.Set(m_SelectedPoint, ' ');
			m_IsFirstMove = false;
		}

		uint32_t currentMovesCount = m_MovesLeft;
		m_Map.ProcessClick(m_SelectedPoint,&m_MovesLeft);
		m_Score += currentMovesCount - m_MovesLeft;
	}
	else if (m_Score >= m_Map.GetSize() * m_Map.GetSize() - 40) {
		ClearScreen();
		m_Map.DrawMines();
		std::cout << "You Win!\n";
		std::cout << "Score: " << m_Score << '\n';
		std::cin.ignore();
		m_Exit = true;
	}
	else {
		m_Map.DrawMines();
		std::cout << "Game Over\n";
		std::cout << "Score: " << m_Score << '\n';
		std::cin.ignore();
		m_Exit = true;
	}
}
