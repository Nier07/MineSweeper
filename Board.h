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
	std::vector<std::unique_ptr<Node>> board;
	int rows, cols, mines, size;

	Board();
	Board(Difficulty dif);
	//custom Board constructor
	Board(int rows, int cols, int mines);

private:
	void setDifficulty(Difficulty dif);
	void initBoard(int size);
	void generateMines();
	void calculateAdjacency();
	bool adjacencyCheck(int x, int horizontalCheck, Node::NodeType type);
};