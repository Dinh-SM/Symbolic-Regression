#include "Node.h"
#include <cstring>
#include <cstdlib>
#include<string>

// Constructor
Node::Node(Node* lc, Node* rc, std::string v)
{
	left_child_ = lc;
	right_child_ = rc;
	value_ = v;
};

// Copy Constructor
Node::Node(Node &root)
{
	if(root.left_child() != NULL && root.right_child() != NULL)
	{
		value_ = root.value();

		Node* lc = new Node(*root.left_child());
		left_child_ = lc;
		*left_child_ = *lc;

		Node* rc = new Node(*root.right_child());
		right_child_ = rc;
		*right_child_ = *rc;
	}
	else if(root.left_child() != NULL && root.right_child() == NULL)
	{
		value_ = root.value();

		Node* lc = new Node(*root.left_child());
		left_child_ = lc;
		*left_child_ = *lc;

		right_child_ = NULL;
	}
	else if(root.left_child() == NULL && root.right_child() == NULL)
	{
		value_ = root.value();

		left_child_ = NULL;

		right_child_ = NULL;
	}
};

// Destructor
Node::~Node()
{
	value_.clear();
};

// Getters
Node* Node::left_child()
{
	return left_child_;
};

Node* Node::right_child()
{
	return right_child_;
};

std::string Node::value()
{
	return value_;
};

// Setters
void Node::set_left_child(Node* lc)
{
	left_child_ = lc;
};

void Node::set_right_child(Node* rc)
{
	right_child_ = rc;
};

void Node::set_value(int b){
	value_=b;
}


//Function
int Node::node_result()
{
	if(std::strcmp(value_.c_str(), "AND") == 0)
	{
		return left_child_->node_result() && right_child_->node_result();
	}
	else if(std::strcmp(value_.c_str(), "OR") == 0)
	{
		return left_child_->node_result() || right_child_->node_result();
	}
	else if(std::strcmp(value_.c_str(), "NOT") == 0)
	{
		return !left_child_->node_result();
	}
	else
	{
		return std::atoi(value_.c_str());
	}
};

int Node::node_result(int x1, int x2)
{
	if(std::strcmp(value_.c_str(), "AND") == 0)
	{
		return left_child_->node_result() && right_child_->node_result();
	}
	else if(std::strcmp(value_.c_str(), "OR") == 0)
	{
		return left_child_->node_result() || right_child_->node_result();
	}
	else if(std::strcmp(value_.c_str(), "NOT") == 0)
	{
		return !left_child_->node_result();
	}
	else if(std::strcmp(value_.c_str(), std::to_string(x1).c_str()) == 0)
	{
		return x1;
	}
	else if(std::strcmp(value_.c_str(), std::to_string(x2).c_str()) == 0)
	{
		return x2;
	}
	else
	{
		return std::atoi(value_.c_str());
	}
};

std::string Node::node_formula()
{
	if(std::strcmp(value_.c_str(), "AND") == 0)
	{
		return '(' + left_child_->node_formula() + " " + value_ + " " + right_child_->node_formula() + ')';
	}
	else if(std::strcmp(value_.c_str(), "OR") == 0)
	{
		return '(' + left_child_->node_formula() + " " + value_ + " " + right_child_->node_formula() + ')';
	}
	else if(std::strcmp(value_.c_str(), "NOT") == 0)
	{
		return '(' + value_ + " " + left_child_->node_formula() + ')';
	}
	else
	{
		return value_;
	}
};
