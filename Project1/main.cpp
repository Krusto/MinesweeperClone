#include <iostream>
#include <Windows.h>
#include "Minesweeper.h"
#include "WindowsFunctions.h"

int main() {

	ShowConsoleCursor(false);
	system("mode 35,20");


	Minesweeper::Game game;
	game.Init();

	while (!game.IsReadyToExit()) {
		game.Update();
	}

}