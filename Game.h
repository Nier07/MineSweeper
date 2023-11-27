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

	Board board;

	std::string userInput;
	int userPos[3];
	bool systemExit;

	Game();
	void startGame();

private:
	void playGame(const Board& game);
	void consoleInput();
	void splitInput();
	void endGame();
	void swapScreen(CurrentScreen screen);
	bool isNumber(const std::string& s);
};