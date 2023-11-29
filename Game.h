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
	int userPos[3];
	bool systemExit, userFlag;

	Game();
	void startGame();

private:
	void playGame();
	void consoleInput();
	void gameInput(const int&& x);
	void splitInput();
	void endGame();
	void swapScreen(CurrentScreen screen);
	bool isNumber(const std::string& s);
};