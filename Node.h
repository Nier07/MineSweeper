#pragma once
#include <string>
#include <iostream>

class Node {
public:
	enum NodeType {
		empty,
		clue,
		mine
	};

	NodeType type;

	int pos;
	bool isRevealed, isFlagged;
	//used for output
	std::string sprite;

	Node();
	Node(int pos);
	//reveal behaviour changes based on which child node is calling it
	virtual bool reveal();
	void flag();
private:



};