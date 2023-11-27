#include "Game.h"
#include "UI.h"
#include <sstream>

Game::Game() {
	this->systemExit = false;
}

void Game::startGame(){
	swapScreen(mainMenu);
}

void Game::consoleInput() {
	std::cout << std::endl << "Input: ";
	std::getline(std::cin, userInput);

	splitInput();
}

void Game::splitInput() {
	//for GUI naviagation just user userPos[0] for the actual game can use both userPos[0] and userPos[1];
	std::istringstream ss(this->userInput);
	std::string word;

	int index = 0;
	while (getline(ss, word, ' ')) {
		if (word == "FLAG" || word == "QUIT") systemExit = true;
		else if (isNumber(word)) {
			userPos[index] = stoi(word);
			index++;
		}
		else consoleInput();
	}
}

bool Game::isNumber(const std::string& s) {
	return !s.empty() && find_if(s.begin(), s.end(), [](unsigned char c) {
	return !isdigit(c); }) == s.end();
}

void Game::swapScreen(CurrentScreen screen) {
	while(!systemExit){
		switch (screen) {
			case mainMenu:
				UI::mainMenu();
				consoleInput();

				if (userPos[0] == 1) screen = difficultySelect;
				if (userPos[0] == 2) screen = instructions;
				if (userPos[0] == 3) systemExit = true;
				break;

			case instructions:
				UI::instructions();
				consoleInput();

				if (userPos[0] == 1) screen = mainMenu;
				break;

			case difficultySelect:
				UI::difficultySelect();
				consoleInput();

				if (userPos[0] == 1) {
					this->board = Board(Board::easy);
					screen = gameScreen;
				}
				if (userPos[0] == 2) {
					this->board = Board(Board::medium);
					screen = gameScreen;
				}
				if (userPos[0] == 3) {
					this->board = Board(Board::hard);
					screen = gameScreen;
				}

				if (userPos[0] == 4) screen = customDifficulty;
				if (userPos[0] == 5) screen = mainMenu;
				break;
			case customDifficulty:
				UI::createCustomDifficulty();
				consoleInput();
				this->board = Board(userPos[0], userPos[1], userPos[2]);
				screen = gameScreen;
				break;
			case gameScreen:
				playGame(this->board);
				//temp
				systemExit = true;
				break;
			case loseScreen:
				UI::loseScreen();
				consoleInput();
				break;
			case winScreen:
				UI::winScreen();
				consoleInput();
				break;
			default:
				systemExit = true;
				break;
		}
	}
}

void Game::playGame(const Board& game) {
    for (const auto& node : game.board) {
        if (node->pos % game.cols == 0) std::cout << std::endl;
        std::cout << std::to_string(node->type) << " ";
    }

    std::cout << std::endl;

    for (const auto& node : game.board) {
        if (node->pos % game.cols == 0) std::cout << std::endl;
        node->reveal();
        std::cout << node->sprite << " ";
    }
}

void Game::endGame() {
	exit(1);
}