#include "Node.h"

Node::Node() {
	type = empty;
	isRevealed = false;
	isFlagged = false;
	pos = 0;
	sprite = "?";
}

Node::Node(int pos) {
	type = empty;
	isRevealed = false;
	isFlagged = false;
	this->pos = pos;
	sprite = "?";
}

bool Node::reveal() {
	//returns false if a node is already revealed
	if (isRevealed) return false;
	else {
		//return true when revealing a ndoe and change its sprite
		sprite = "0";
		isRevealed = true;
		return isRevealed;
	}
}

void Node::flag(){
	//makes it so revealed nodes cant be flaged
	if (isRevealed) return;

	//toggles flag
	if (isFlagged) sprite = "?";
	else sprite = 'f';

	isFlagged = !isFlagged;
}