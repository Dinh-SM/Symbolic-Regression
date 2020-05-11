#include<string>

class Node
{
	public:
		// Constructor
		Node(Node* lc, Node* rc, std::string v);

		// Destructor
		~Node();
		
		// Getters
		Node* left_child();
		Node* right_child();
		std::string value();

		int node_result();

	protected:
		Node* left_child_;
		Node* right_child_;
		std::string value_; // operation or operator
};