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
	GotoXY(0,0);
	if (!m_IsGameover) {
		m_Map.Draw();

		std::cout << "Score : 0\nPlease enter coordinate : ";

		std::cin >> m_SelectedPoint.x >> m_SelectedPoint.y;

		if (!m_Map.IsValid(m_SelectedPoint))
			return;

		if (m_Map.IsMine(m_SelectedPoint) && !m_IsFirstMove) 
			m_IsGameover = true;

		if (m_IsFirstMove && m_Map.IsMine(m_SelectedPoint)) {
			m_Map.Set(m_SelectedPoint, ' ');
			m_IsFirstMove = false;
		}

		m_Map.ProcessClick(m_SelectedPoint,&m_MovesLeft);
	}
	else {
		m_Map.DrawMines();
		std::cout << "Game Over\n";
		
		std::cin.ignore();
	}
}
