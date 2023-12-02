#pragma once
#include "Board.h"

class Game {
public:
	enum CurrentScreen {
		mainMenu,
		instructions,
		difficultySelect,
		customDifficulty,
		gameScreen,
		loseScreen,
		winScreen
	};

	CurrentScreen screen;

	Board game;

	std::string userInput;
	unsigned int userPos[3];
	bool systemExit, userFlag;

	Game();
	void startGame();
	void endGame();

private:
	void checkWin();
	void printGame();
	void playGame();
	void consoleInput();
	void gameInput(const int&& x);
	bool splitInput();
	void swapScreen(CurrentScreen screen);
	bool isNumber(const std::string& s);
};