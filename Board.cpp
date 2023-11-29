#include "Mine.h"
#include "Clue.h"
#include "Board.h"

Board::Board() {
	rows = 0;
	cols = 0;
	mines = 0;
	size = 0;
	dif = empty;
}

Board::Board(Difficulty dif) {
	setDifficulty(dif);
	initBoard();
}

//custom difficulty takes user input
Board::Board(int rows, int cols, int mines) {
	this->rows = (rows > 100) ? 100 : rows;
	this->cols = (cols > 70) ? 70 : cols;

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
	if (board.at(x)->isFlagged) return false;
	//checks if x is the desired type
	if (board.at(x)->type == type) return true;
	return false;
}

bool Board::adjacencyCheck(int x, int horizontalCheck) {
	if (!inBoard(x)) return false;
	if ((x + horizontalCheck) == -1) return false;
	if (x / cols != horizontalCheck / cols) return false;
	//does not reveal flaggged nodes
	if (board.at(x)->isFlagged) return false;
	return true;
}

bool Board::inBoard(int x) {
	//checks if x is in within the bounds of the vector
	if (x >= 0 && x < size) return true;
	return false;
}

bool Board::checkEmpty(int x) {
	//returns true if the node at x is empty and hasnt been checked before
	//reveal only returns true the first time its called by a specific node
	if (board.at(x)->type == Node::empty && board.at(x)->reveal()) return true;
	board.at(x)->reveal();
	return false;
}

//this function only gets called if a empty node is revealed by player input
void Board::revealAdjacent(int x) {
	//pushes inital position to stack
	emptyNodeStack.push(x);

	int below, above, current;

	while (!emptyNodeStack.empty()) {
		//sets x to variable at top of stack
		current = emptyNodeStack.top();

		//deletes the top of the stack
		emptyNodeStack.pop();

		below = current + cols;
		above = current - cols;

		//checks adjacency and reveals the nodes if adjacent then pushes that position to the stack for recursion if it is an empty node
		if (adjacencyCheck(current + 1, current) && checkEmpty(current + 1)) emptyNodeStack.push(current + 1);
		if (adjacencyCheck(current - 1, current) && checkEmpty(current - 1)) emptyNodeStack.push(current - 1);
		if (adjacencyCheck(below + 1, below) && checkEmpty(below + 1)) emptyNodeStack.push(below + 1);
		if (adjacencyCheck(below - 1, below) && checkEmpty(below - 1)) emptyNodeStack.push(below - 1);
		if (adjacencyCheck(below, below) && checkEmpty(below)) emptyNodeStack.push(below);
		if (adjacencyCheck(above + 1, above) && checkEmpty(above + 1)) emptyNodeStack.push(above + 1);
		if (adjacencyCheck(above - 1, above) && checkEmpty(above - 1))  emptyNodeStack.push(above - 1);
		if (adjacencyCheck(above, above) && checkEmpty(above)) emptyNodeStack.push(above);
	}
}

void Board::revealAll() {
	//loops through board revealing every node
	for(const auto& node : board){
		node->reveal();
	}
}