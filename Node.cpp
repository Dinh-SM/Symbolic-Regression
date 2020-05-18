#include "Node.h"
#include <cstring>
#include <cstdlib>
#include<string>
#include<iostream>

// Constructor

Node::Node(Node* lc, Node* rc, std::string v)
{
	left_child_ = lc;
	right_child_ = rc;
	value_ = v;
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
		return value_.c_str();
	}
};
