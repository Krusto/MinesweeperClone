#include <iostream>
#include <Windows.h>
#include "Minesweeper.h"
#include "WindowsFunctions.h"

int main() {

	ShowConsoleCursor(false);
	system("mode 30,30");


	Minesweeper::Game game;
	game.Init();

	bool exit = false;
	while (!exit) {
		game.Update();
	}

}