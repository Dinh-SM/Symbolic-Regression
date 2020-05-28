#include "Node.h"
#include <cstring>
#include <cstdlib>
#include<string>

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
	std::cout << "Test 4.5 " << right_child_->value() << std::endl;
};

/*void Node::set_value(std::string b){
	value_ = b;
};*/


//Function
/*void Node::delete_blood(){
	if (left_child_!=NULL && right_child_!=NULL){
		left_child_->delete_blood();
		right_child_->delete_blood();
		delete left_child_;
		left_child_==NULL;
		delete right_child_;
		right_child_==NULL;
	}
	else if (left_child_!=NULL && right_child_==NULL){
		left_child_->delete_blood();
		delete left_child_;
		left_child_==NULL;
	}
	else if (left_child_==NULL && right_child_!=NULL){
		right_child_->delete_blood();
		delete right_child_;
		right_child_==NULL;
	};

	int a = rand() % 2;
	if (a==0){
		set_value(operand_true);	
	}else{
		set_value(operand_false);
	}
};*/

int Node::node_result()
{
	if(value_.compare("AND") == 0)
	{
		return left_child_->node_result() && right_child_->node_result();
	}
	else if(value_.compare("OR") == 0)
	{
		return left_child_->node_result() || right_child_->node_result();
	}
	else if(value_.compare("NOT") == 0)
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
	if(value_.compare("AND") == 0)
	{
		return left_child_->node_result() && right_child_->node_result();
	}
	else if(value_.compare("OR") == 0)
	{
		return left_child_->node_result() || right_child_->node_result();
	}
	else if(value_.compare("NOT") == 0)
	{
		return !left_child_->node_result();
	}
	else if(value_.compare(std::to_string(x1)) == 0)
	{
		return x1;
	}
	else if(value_.compare(std::to_string(x2)) == 0)
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
	if(value_.compare("AND") == 0)
	{
		return '(' + left_child_->node_formula() + " " + value_ + " " + right_child_->node_formula() + ')';
	}
	else if(value_.compare("OR") == 0)
	{
		return '(' + left_child_->node_formula() + " " + value_ + " " + right_child_->node_formula() + ')';
	}
	else if(value_.compare("NOT") == 0)
	{
		return '(' + value_ + " " + left_child_->node_formula() + ')';
	}
	else
	{
		return value_;
	}
};


/*//Operator
	//==
bool Node::operator== (const Node* second) const {
	if (this->value_ == second->value_){

		if(this->left_child_ == second->left_child_){
	
			if(this->right_child_ == second->right_child_){

				return true;

			}
			else{

				return false;
			
			}

		}
		else{

			return false;

		} 

	}
	else{

		return false;

	}
};

	//!=
bool Node::operator!= (const Node* second) const {
	if (this->value_ != second->value_){

		if(this->left_child_ != second->left_child_){
	
			if(this->right_child_ != second->right_child_){

				return true;

			}
			else{

				return false;
			
			}

		}
		else{

			return false;

		} 

	}
	else{

		return false;

	}
};*/