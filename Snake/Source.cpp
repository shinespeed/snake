#include <conio.h>
#include <stdio.h>
#include <windows.h>

#include "Game.h"

void main() {
	system("mode 40, 30");
	Game g;
	
	g.Run();
	_getch();
}