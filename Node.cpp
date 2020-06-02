#include "Node.h"
#include <cstring>
#include <cstdlib>

//Constants, variables
const std::string operator_or("|");
const std::string operator_and("&");
const std::string operator_not("~");

// Default Constructor
Node::Node()
{
	left_child_ = NULL;
	right_child_ = NULL;
	value_ = '\0';
};

// Constructor
Node::Node(Node* lc, Node* rc, std::string v)
{
	left_child_ = lc;
	right_child_ = rc;
	value_ = v;
};

// Copy Constructor
// makes a deep copy of the Node including its children
Node::Node(Node &root)
{
	if(root.left_child() != NULL && root.right_child() != NULL)
	{
		// copy of the value
		value_ = root.value();

		// copy the left child
		Node* lc = new Node(*root.left_child()); // recursive call on left child
		left_child_ = lc;
		*left_child_ = *lc;

		// copy the right child
		Node* rc = new Node(*root.right_child()); // recursive call on right child
		right_child_ = rc;
		*right_child_ = *rc;
	}
	else if(root.left_child() != NULL && root.right_child() == NULL)
	{
		// copy of the value
		value_ = root.value();

		// copy the left child
		Node* lc = new Node(*root.left_child()); // recursive call on left child
		left_child_ = lc;
		*left_child_ = *lc;

		right_child_ = NULL; // we defined that if the Node were to have only one child, it would be the left one
	}
	else if(root.left_child() == NULL && root.right_child() == NULL)
	{
		// copy of the value
		value_ = root.value();

		left_child_ = NULL;

		right_child_ = NULL;
	}
};

// Getters
// returns the pointer on the left child
Node* Node::left_child()
{
	return left_child_;
};

// returns the pointer on the right child
Node* Node::right_child()
{
	return right_child_;
};

// returns the value of the Node
std::string Node::value()
{
	return value_;
};

// Setters
// changes the pointer pointing on the left child
void Node::set_left_child(Node* lc)
{
	left_child_ = lc;
};

// changes the pointer pointing on the right child
void Node::set_right_child(Node* rc)
{
	right_child_ = rc;
};

// changes the value of the current Node
void Node::set_value(std::string s){
	value_ = s;
};


//Functions
// computes and returns the results of one line of the csv file at the current Node
int Node::node_result(std::vector<int> x)
{
	if(value_.compare(operator_and) == 0) // if the value is AND
	{
		return left_child_->node_result(x) && right_child_->node_result(x); // computes left child && right child
	}
	else if(value_.compare(operator_or) == 0) // if the value is OR
	{
		return left_child_->node_result(x) || right_child_->node_result(x); // computes left child || right child
	}
	else if(value_.compare(operator_not) == 0) // if the value is NOT
	{
		return !left_child_->node_result(x); // computes !(left child) (only child is always on the left)
	}
	else
	{
		return x[std::atoi(value_.c_str())-1]; // returns the value of the corresponding gene (1 or 0)
	}
};

// computes and returns the formula at the current Node
std::string Node::node_formula()
{
	if(value_.compare(operator_and) == 0) // if the value is AND
	{
		return '(' + left_child_->node_formula() + " " + value_ + " " + right_child_->node_formula() + ')'; // returns (left child AND right child)
	}
	else if(value_.compare(operator_or) == 0) // if the value is OR
	{
		return '(' + left_child_->node_formula() + " " + value_ + " " + right_child_->node_formula() + ')'; // returns (left child OR right child)
	}
	else if(value_.compare(operator_not) == 0) // if the value is NOT
	{
		return '(' + value_ + left_child_->node_formula() + ')'; // returns (NOT left child)
	}
	else
	{
		return 'x' + value_; // returns x[id of gene]
	}
};