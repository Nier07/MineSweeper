#include "Game.h"
#include "UI.h"
#include <sstream>
#include <iomanip>

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
	userFlag = false;

	int index = 0;
	while (getline(ss, word, ' ')) {
		if (word == "QUIT") systemExit = true;
		else if (word == "FLAG") userFlag = true;
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
				if (userPos[0] == 2) screen = difficultySelect;
				break;

			case difficultySelect:
				UI::difficultySelect();
				consoleInput();

				if (userPos[0] == 1) {
					this->game = Board(Board::easy);
					screen = gameScreen;
				}
				if (userPos[0] == 2) {
					this->game = Board(Board::medium);
					screen = gameScreen;
				}
				if (userPos[0] == 3) {
					this->game = Board(Board::hard);
					screen = gameScreen;
				}

				if (userPos[0] == 4) screen = customDifficulty;
				if (userPos[0] == 5) screen = mainMenu;
				break;
			case customDifficulty:
				UI::createCustomDifficulty();
				consoleInput();
				this->game = Board(userPos[0], userPos[1], userPos[2]);
				screen = gameScreen;
				break;
			case gameScreen:
				playGame();
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

void Game::playGame() {
	std::cout << std::setw(3) << std::left << "    " ;

	for (int i = 1; i < game.cols + 1; i++) {
        std::cout << std::setw(3) << std::left << i ;
    }

    std::cout << std::endl;

    for (const auto& node : game.board) {
        if (node->pos % game.cols == 0) std::cout << std::endl << std::setw(4) << std::left << node->pos / game.cols + 1  ;
        std::cout << std::setw(3) << std::left << node->sprite;
    }

	consoleInput();
	gameInput((userPos[0] - 1) * game.cols + userPos[1] - 1);
}

void Game::gameInput(const int&& x) {

	if (!game.inBoard(x)) return;
	if (userFlag) {
		game.board.at(x)->flag();
		return;
	}

	if (game.board.at(x)->isFlagged) return;
	game.board.at(x)->reveal();

	if (game.board.at(x)->type == Node::empty) game.revealAdjacent(x);
};

void Game::endGame() {
	exit(1);
}