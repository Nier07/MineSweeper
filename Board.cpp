#include "Mine.h"
#include "Clue.h"
#include "Board.h"

Board::Board() {
	rows = 0;
	cols = 0;
	mines = 0;
	size = rows * cols;
	dif = empty;
}

Board::Board(Difficulty dif) {
	setDifficulty(dif);
	initBoard();
}

//custom difficulty takes user input
Board::Board(int rows, int cols, int mines) {
	if (rows > 100) this->rows = 100;
	else this->rows = rows;
	if (cols > 70) this->cols = 70;
	else this->cols = cols;

	size = this->rows * this->cols;
	if (mines > size)this->mines = size;
	else this->mines = mines;
	dif = custom;

	initBoard();
}

void Board::setDifficulty(Difficulty dif) {
	//sets board sizes based on difficulty
	switch (dif) {
		case easy:
			rows = 5;
			cols = 5;
		    mines = 4;
			break;
		case medium:
			rows = 8;
			cols = 8;
			mines = 15;
			break;
		case hard:
			rows = 10;
			cols = 10;
			mines = 25;
			break;
		default:
			std::cout << "Passed Non-existant Difficulty Type" << std::endl;
			break;
	}

	this->size = rows * cols;
}

void Board::initBoard() {
	//initalizes the board
	for (int i = 0; i < size; i++) {
		board.push_back(std::make_unique<Node>(i));
	}

	generateMines();
	calculateAdjacency();
}

void Board::generateMines() {
	//makes random work
	srand(time(0));

	for (int i = 0; i < mines; i++) {
		int minePos = rand() % size;

		//checks if the node at minePos is empty if it is then creates a mine object at that position in the array
		if (board.at(minePos)->type == Node::empty) {
			board.at(minePos) = std::make_unique<Mine>(minePos);
		}
		//if the node was not empty then it was a mine so i should decrement as a mine wasnt created
		else {
			i--;
		}
	}
}

void Board::calculateAdjacency() {
	for (const auto& node : board) {
		if (node->type == Node::empty) {
			int adjMines = 0;
			int current = node->pos;
			int below = node->pos + cols;
			int above = node->pos - cols;

			//checks all adjacent nodes if they are mines increase mine counter
			if (adjacencyCheck(current + 1, current, Node::mine)) adjMines++;
			if (adjacencyCheck(current - 1, current, Node::mine)) adjMines++;
			if (adjacencyCheck(below + 1, below, Node::mine)) adjMines++;
			if (adjacencyCheck(below - 1, below, Node::mine)) adjMines++;
			if (adjacencyCheck(below, below, Node::mine)) adjMines++;
			if (adjacencyCheck(above + 1, above, Node::mine)) adjMines++;
			if (adjacencyCheck(above - 1, above, Node::mine)) adjMines++;
			if (adjacencyCheck(above, above, Node::mine)) adjMines++;

			//create a clue object at the current position in the vector initalized with the caulated adjacent mines 
			if (adjMines > 0) board.at(current) = std::make_unique<Clue>(adjMines, current);
		}
	}
}

bool Board::adjacencyCheck(int x, int horizontalCheck, Node::NodeType type) {
	//fixes bug with the node at pos cols-1 detecting mines at pos 0 when checking top right node
	if ((x + horizontalCheck) == -1) return false;
	if(!inBoard(x)) return false;
	//checks that cells to the left or right of x are in the same row
	if (x / cols != horizontalCheck / cols) return false;
	//checks if x is the desired type
	if (board.at(x)->type == type) return true;
	return false;
}

bool Board::adjacencyCheck(int x, int horizontalCheck) {
	if ((x + horizontalCheck) == -1) return false;
	if (!inBoard(x)) return false;
	if (x / cols != horizontalCheck / cols) return false;
	//does not reveal flaggged nodes
	if (board.at(x)->isFlagged) return false;
	revealRecursion(x);
	return true;
}

void Board::revealRecursion(int x) {
	//when an adjacent node is empty and revealed then call revealAdjacent with that node
	if (board.at(x)->type == Node::empty && board.at(x)->reveal()) revealAdjacent(x);
	board.at(x)->reveal();
}

bool Board::inBoard(int x) {
	//checks if x is in within the bounds of the vector
	if (x >= 0 && x < size) return true;
	return false;
}

void Board::revealAdjacent(int x) {
	int below = x + cols;
	int above = x - cols;

	//checks adjacency and reveals the nodes if adjacent
	adjacencyCheck(x + 1, x);
	adjacencyCheck(x - 1, x);
	adjacencyCheck(below + 1, below);
	adjacencyCheck(below - 1, below);
	adjacencyCheck(below, below);
	adjacencyCheck(above + 1, above);
	adjacencyCheck(above - 1, above);
	adjacencyCheck(above, above);
}

void Board::revealAll() {
	//loops through board revealing every node
	for(const auto& node : board){
		node->reveal();
	}
}