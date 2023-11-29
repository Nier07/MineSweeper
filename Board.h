#pragma once
#include <vector>
#include <memory>
#include "Node.h"

class Board {
public:
	enum Difficulty {
		empty,
		easy,
		medium,
		hard,
		custom
	};

	Difficulty dif;

	//vector of unqiue pointers to a node object
	//this is used so that children of Node can be added to the vector
	//then lets me use polymorphism to call different stuff depending on the speicifc Node child
	//could have been a Node** but then i would have to write a destructor, copy/copy assignment constructor and maybe even a move/move assignment constructor
	//we havent really learnt that yet so i opted for rule of 0 using unqiue pointers and vectors
	//this helps give better memory management
	std::vector<std::unique_ptr<Node>> board;
	int rows, cols, mines, size;
	

	Board();
	Board(Difficulty dif);
	//custom Board constructor
	Board(int rows, int cols, int mines);
	bool inBoard(int x);
	void revealAdjacent(int x);
	void initBoard();
	void revealAll();

private:
	void revealRecursion(int x);
	void setDifficulty(Difficulty dif);
	void generateMines();
	void calculateAdjacency();
	bool adjacencyCheck(int x, int horizontalCheck, Node::NodeType type);
	bool adjacencyCheck(int x, int horizontalCheck);
};