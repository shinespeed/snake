#pragma once

#include <vector>
#include <windows.h>

class Game {
public:
	Game();
	~Game();
	void Run();
 private:
	void ShowConsoleCursor(bool showFlag);
	void PrintElement(COORD c, int color);

	void ShowSnake();
	void HideSneak();
	void MoveSnake();

	void FillTheField();
	void HandleButtons();

	void GetElement();
	void GenerateFood();
	void ShowFood();
	void HideFood();
	void EatFood();

	bool isOver();
	void GameOver();

	static const int ROW = 30, COL = 40;
	int field[ROW][COL];
	std::vector<COORD> snake_;
	COORD startCoordinates_;
	enum class Ways { UP, RIGHT, DOWN, LEFT };//enum class Ways
	Ways way_;
	COORD coordsOfFood_;
};