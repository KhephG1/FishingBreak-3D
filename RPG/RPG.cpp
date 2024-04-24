#include "stdafx.h"
#include "Game.h"
#include <Windows.h>
//Every game should have a game class

int main()
{
	Game game{};
	//HWND hwnd = GetConsoleWindow();
	//ShowWindow(hwnd, SW_HIDE);
	game.run();
	return 0;
}