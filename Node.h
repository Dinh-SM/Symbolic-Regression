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
		//! Makes a deep copy of the Node including its children
		Node(Node &root);

		// Getters
		//! Returns the pointer on the left child
		Node* left_child();
		
		//! Returns the pointer on the right child
		Node* right_child();
		
		//! Returns the value of the Node
		std::string value();

		// Setters
		//! Changes the pointer pointing on the left child
		void set_left_child(Node* lc);

		//! Changes the pointer pointing on the right child
		void set_right_child(Node* rc);

		//! Changes the value of the current Node
		void set_value(std::string s);

		//Fonctions
		//! Computes and returns the results of one line of the csv file at the current Node
		int node_result(std::vector<int> x);
		
		//! Computes and returns the formula at the current Node
		std::string node_formula();

	protected:
		// Attributes
		Node* left_child_; //! Pointer on the left child
		Node* right_child_; //! Pointer on the right child
		std::string value_; //! Operation or operator
};
