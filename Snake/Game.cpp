#include "Game.h"

#include <conio.h>

#include <thread>
#include <chrono>

Game::Game()
{
	ShowConsoleCursor(false);
	startCoordinates_.X = 20;
	startCoordinates_.Y = 15;
	snake_.emplace_back(startCoordinates_);

	ShowSnake();

	way_ = Ways::UP;

	GenerateFood();
	ShowFood();
}

void Game::ShowConsoleCursor(bool showFlag) {
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_CURSOR_INFO     cursorInfo;

	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = showFlag; // set the cursor visibility
	SetConsoleCursorInfo(out, &cursorInfo);
}

void Game::FillTheField() {
	for (int i = 0; i < ROW; ++i) {
		for (int j = 0; j < COL; ++j) {
			field[i][j] = 0;
		}
	}
}

void Game::PrintElement(COORD c, int color) {
	static HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
	static DWORD written;
	//COORD c;
	//c.X = x;
	//c.Y = y;
	//FillConsoleOutputAttribute(hout, FOREGROUND_GREEN | BACKGROUND_RED, 1, c, &written);
	FillConsoleOutputAttribute(hout, color, 1, c, &written);
}

void Game::ShowSnake() {
	for (int i = 0; i < snake_.size(); ++i) {
		PrintElement(snake_.at(i), 120);
	}
}

void Game::HideSneak() {
	for (int i = 0; i < snake_.size(); ++i) {
		PrintElement(snake_.at(i), 0);
	}
}

void Game::MoveSnake() {
	HideSneak();
	for (int i = (snake_.size() - 1); i > 0; --i) {
		snake_.at(i) = snake_.at(i - 1);
	}
	if (!(int)way_) {
		--snake_.at(0).Y;
		EatFood();
	}
	else if ((int)way_ == 1) {
		++snake_.at(0).X;
		EatFood();
	}
	else if ((int)way_ == 2) {
		++snake_.at(0).Y;
		EatFood();
	}
	else if ((int)way_ == 3) {
		--snake_.at(0).X;
		EatFood();
	}
	ShowSnake();
	std::this_thread::sleep_for(std::chrono::milliseconds(100));
}

void Game::HandleButtons() {
	enum Keys { UP = 72, DOWN = 80, LEFT = 75, RIGHT = 77, ENTER = 10, ESCAPE = 27 };
	unsigned char a;
	/*while (1)
	{*/
		a = _getch();
		/*if (a == 0 || a == 0xE0) {
			a = _getch();
		}*/
		//if (a == ESCAPE) {//ESC for exit the 'while'
		//	break;
		//}
		if (a == UP && (int)way_ != 2) {//up
			way_ = Ways::UP;
			//MoveSnake();
		}
		else if (a == DOWN && (int)way_ != 0) {//down
			way_ = Ways::DOWN;
			//MoveSnake();
		}
		else if (a == LEFT && (int)way_ != 1) {//left
			way_ = Ways::LEFT;
			//MoveSnake();
		}
		else if (a == RIGHT && (int)way_ != 3) {//right
			way_ = Ways::RIGHT;
			//MoveSnake();
		}
	//}
}

void Game::GetElement() {
	COORD c;
	c.X = 40;// Snake.at(0).X;
	c.Y = 30;// Snake.at(0).Y;
	snake_.emplace_back(c);
}

void Game::GenerateFood() {
	srand(time(0));
	int x, y;
	int t = 1;
	while (true) {
		x = (rand() % 40);
		y = (rand() % 30);
		for (int i = 0; i < snake_.size(); ++i) {
			if (snake_.at(i).X != x || snake_.at(i).Y != y) {
				t *= 1;
			}
			else { t *= 0; }
		}
		if (t) { break; }
	}
	field[y][x] = 1;
	coordsOfFood_.X = x;
	coordsOfFood_.Y = y;

	ShowFood();
}

void Game::ShowFood() {
	PrintElement(coordsOfFood_, 120);
}

void Game::HideFood() {
	PrintElement(coordsOfFood_, 0);
}

void Game::EatFood() {
	if (field[snake_.at(0).Y][snake_.at(0).X]) {
		GetElement();
		field[snake_.at(0).Y][snake_.at(0).X] = 0;
		GenerateFood();
		//printf("%d", Snake.size());
		//printf("%d %d",Snake.at(Snake.size() - 1).X, Snake.at(Snake.size() - 1).Y);
	}
}

void Game::GameOver() {
	system("cls");
	printf("\t\tGame Over\n");
	printf("Score: %d", snake_.size());
}

bool Game::isOver() {
	for (int i = 0; i < snake_.size(); ++i) {
		if (i > 0 && snake_.at(i).X == snake_.at(0).X && snake_.at(i).Y == snake_.at(0).Y) {
			return true;
		}
	}
	if (snake_.at(0).X > 39 || snake_.at(0).X < 0 || snake_.at(0).Y > 29 || snake_.at(0).Y < 0) {
		return true;
	}
	else {
		return false;
	}
}

void Game::Run() {
	while (true) {
		if (_kbhit()) {
			HandleButtons();
		}
		MoveSnake();
		if (isOver()) { break; }
	}
	GameOver();
}

Game::~Game()
{
}