#pragma once
#include "Node.h"

class Clue : public Node {
public:
	int adjacentMines;

	Clue(int adjacentMines, int pos);
	bool reveal() override;
};