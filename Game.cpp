#include "Game.h"
#include "UI.h"
#include <sstream>
#include <iomanip>

Game::Game() {
	systemExit = false;
}

void Game::startGame(){
	swapScreen(mainMenu);
}

void Game::consoleInput() {
	std::cout << std::endl << "Input: ";
	std::getline(std::cin, userInput);
	std::cout << std::endl;

	bool continueReccursion = splitInput();

	if (!continueReccursion) return;

	consoleInput();
}

bool Game::splitInput() {
	//for GUI naviagation just user userPos[0] for the actual game can use both userPos[0] and userPos[1];
	std::istringstream ss(userInput);
	std::string word;
	userFlag = false;
	//fills userPos with 0s
	std::fill_n(userPos, 3, 0);

	int index = 0;
	//get each word from the string stream using a space as a delimiter
	while (getline(ss, word, ' ')) {
		if (word == "QUIT") endGame();
		else if (word == "FLAG") userFlag = true;
		//each number seperated by a space is added to the userPos array
		else if (isNumber(word)) {
			userPos[index] = stoi(word);
			index++;
			if (index > 3) return true;
		}
		//asks for console output if user types something that isnt a number or FLAG/QUIT
		else return true;
	}
	return false;
}

bool Game::isNumber(const std::string& s) {
	//checks if a string is empty
	if (s.empty()) return false;
	//loops through the string and if a character is not a digit return false
	for (const unsigned char& c : s) {
		if (!isdigit(c)) return false;
		if (c == '-') return false;
	}
	//if all characters are digits then return true
	return true;
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

				//create board based on selected difficulty
				if (userPos[0] == 1) {
					game = Board(Board::easy);
					screen = gameScreen;
				}
				if (userPos[0] == 2) {
					game = Board(Board::medium);
					screen = gameScreen;
				}
				if (userPos[0] == 3) {
					game = Board(Board::hard);
					screen = gameScreen;
				}

				if (userPos[0] == 4) screen = customDifficulty;
				if (userPos[0] == 5) screen = mainMenu;
				break;
			case customDifficulty:
				UI::createCustomDifficulty();
				consoleInput();
				//create board based on inputted rows, cols, mines
				game = Board(userPos[0], userPos[1], userPos[2]);
				screen = gameScreen;
				break;
			case gameScreen:
				playGame();
				break;
			case loseScreen:
				printGame();
				UI::loseScreen();
				consoleInput();
				if (userPos[0] == 1) screen = difficultySelect;
				if (userPos[0] == 2) screen = mainMenu;
				break;
			case winScreen:
				printGame();
				UI::winScreen();
				consoleInput();
				if (userPos[0] == 1) screen = difficultySelect;
				if (userPos[0] == 2) screen = mainMenu;
				break;
			default:
				systemExit = true;
				break;
		}
	}
}

void Game::playGame() {
	checkWin();
	printGame();
	consoleInput();
	//wanted to try passing rvalues into a function
	gameInput((userPos[1] - 1) * game.cols + userPos[0] - 1);
}

void Game::checkWin() {
	int winCounter = 0;
	//checks if each node in gameboard is not a mine and is revealed
	//if it is a nonmine revealed node increase wincounter
	for (const auto& node : game.board) {
		if (node->type != Node::mine && node->isRevealed) winCounter++;
	}
	//when wincounter equals the size of the board - the mines reval the board and swap to win screen
	//this means that all non mine squares have been revealed
	if (winCounter == game.size - game.mines && winCounter > 0) {
		game.revealAll();
		swapScreen(winScreen);
	}
}

void Game::printGame() {
	//spaces for formatting
	std::cout << std::setw(3) << std::left << "    ";

	//prints column numbers
	for (int i = 1; i < game.cols + 1; i++) {
		std::cout << std::setw(3) << std::left << i;
	}

	std::cout << std::endl;

	int flagCount = 0;
	//prints the gameboard and row numbers
	for (const auto& node : game.board) {
		if (node->pos % game.cols == 0) std::cout << std::endl << std::setw(4) << std::left << node->pos / game.cols + 1;
		if (node->isFlagged) flagCount++;
		std::cout << std::setw(3) << std::left << node->sprite;
	}

	std::cout << std::endl <<  "Mines Remaining: " << game.mines - flagCount << std::endl;
}

void Game::gameInput(const int&& x) {
	//checks if x is in the board
	if (!game.inBoard(x)) return;
	//if the user typed FLAG then flags the position
	if (userFlag) {
		game.board.at(x)->flag();
		return;
	}
	//checks if node at position x is not a flagged node
	if (game.board.at(x)->isFlagged) return;
	//reveals node at position x
	game.board.at(x)->reveal();

	//if the revealed node is empty it will autoreveal tiles around it
	if (game.board.at(x)->type == Node::empty) game.revealAdjacent(x);
	//if the revealed node is a mine it will reveal the board and swap to the lose screen
	if (game.board.at(x)->type == Node::mine) {
		game.revealAll();
		swapScreen(loseScreen);
	}

};

void Game::endGame() {
	exit(1);
}