#include "Node.h"

// Constructor
Node::Node(Node lc, Node rc, char* v)
{
	left_child_ = lc;
	right_child_ = rc;
	value_ = v;
};

// Destructor
Node::~Node()
{
	delete []value_;
	left_child_.~Node();
	right_child_.~Node();
};

// Getters
Node Node::left_child()
{
	return left_child_;
};

Node Node::right_child()
{
	return right_child_;
};

char* Node::value()
{
	return value_;
};
