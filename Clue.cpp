#include "Clue.h"

Clue::Clue(int adjacentMines, int pos){
	this->adjacentMines = adjacentMines;
	this->pos = pos;
	type = clue;
	isRevealed = false;
	isFlagged = false;
	sprite = "?";
}

bool Clue::reveal() {
	//checks if node is already revealed
	if (isRevealed) return false;
	else {
		//sets sprite to the number of adjacent mines of this node
		isRevealed = true;
		sprite = std::to_string(adjacentMines);
		return true;
	}
}