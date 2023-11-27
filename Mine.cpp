#include "Mine.h"

Mine::Mine() {
	this->type = mine;
	this->pos = 0;
	this->isRevealed = false;
	this->isFlagged = false;
	this->sprite = "?";
}

Mine::Mine(int pos) {
	this->type = mine;
	this->pos = pos;
	this->isRevealed = false;
	this->isFlagged = false;
	this->sprite = "?";
}

bool Mine::reveal(){
	if (isRevealed) {
		std::cout << "Mine Revealed and game not over";
		//end game
		return false;
	}
	else {
		this->isRevealed = true;
		this->sprite = "x";
		return true;
	}
}