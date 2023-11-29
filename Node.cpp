#include "Node.h"

Node::Node() {
	this->type = empty;
	this->isRevealed = false;
	this->isFlagged = false;
	this->pos = 0;
	this->sprite = "?";
}

Node::Node(int pos) {
	this->type = empty;
	this->isRevealed = false;
	this->isFlagged = false;
	this->pos = pos;
	this->sprite = "?";
}

bool Node::reveal() {
	if (isRevealed) return false;
	else {
		this->sprite = "0";
		this->isRevealed = true;
		return true;
	}
}

void Node::flag(){
	if (isRevealed) return;
	if (isFlagged) sprite = "?";
	else sprite = 'f';

	isFlagged = !isFlagged;
}