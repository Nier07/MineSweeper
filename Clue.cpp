#include "Clue.h"

Clue::Clue(int adjacentMines, int pos){
	this->adjacentMines = adjacentMines;
	this->pos = pos;
	this->type = clue;
	this->isRevealed = false;
	this->isFlagged = false;
	this->sprite = "?";
}

bool Clue::reveal() {
	//checks if node is already revealed
	if (isRevealed) return false;
	else {
		this->isRevealed = true;
		this->sprite = std::to_string(this->adjacentMines);
		return true;
	}
}