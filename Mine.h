#pragma once
#include "Node.h"

class Mine : public Node {
public:
	Mine();
	Mine(int pos);
	bool reveal() override;
};