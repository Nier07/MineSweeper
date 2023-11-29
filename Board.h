#pragma once
#include <vector>
#include <memory>
#include <stack>
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
	//i need to use this instead of recursion because if i have a large custom board
	// eg 70 by 100 with no mines the whole board will autofill as all nodes are empty
	//when using a recursive function this would lead to a stack overflow even with a few optimisations
	//and i didnt really want to implement recursion depth as that would not properly autofill
	std::stack<int> emptyNodeStack;
	bool checkEmpty(int x);
	void setDifficulty(Difficulty dif);
	void generateMines();
	void calculateAdjacency();
	bool adjacencyCheck(int x, int horizontalCheck, Node::NodeType type);
	bool adjacencyCheck(int x, int horizontalCheck);
};