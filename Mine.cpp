#include "Mine.h"

Mine::Mine() {
	type = mine;
	pos = 0;
	isRevealed = false;
	isFlagged = false;
	sprite = "?";
}

Mine::Mine(int pos) {
	type = mine;
	this->pos = pos;
	isRevealed = false;
	isFlagged = false;
	sprite = "?";
}

bool Mine::reveal(){
	//checks if a ndoe is already revealed and changes sprite if not
	if (isRevealed) return false;
	else {
		isRevealed = true;
		sprite = "x";
		return isRevealed;
	}
}