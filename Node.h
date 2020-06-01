#include <string>
#include <vector>

class Node
{
	public:
		// Default Constructor
		Node();

		// Constructor
		Node(Node* lc, Node* rc, std::string v);

		// Copy Constructor
		Node(Node &root); // makes a deep copy of the Node including its children
		
		// Getters
		Node* left_child(); // returns the pointer on the left child
		Node* right_child(); // returns the pointer on the right child
		std::string value(); // returns the value of the Node

		// Setters
		void set_left_child(Node* lc); // changes the pointer pointing on the left child
		void set_right_child(Node* rc); // changes the pointer pointing on the right child
		void set_value(std::string s); // changes the value of the current Node

		//Fonctions
		int node_result(std::vector<int> x); // computes and returns the results of one line of the csv file at the current Node
		std::string node_formula(); // computes and returns the formula at the current Node

	protected:
		Node* left_child_; // pointer on the left child
		Node* right_child_; // pointer on the right child
		std::string value_; // operation or operator
};
