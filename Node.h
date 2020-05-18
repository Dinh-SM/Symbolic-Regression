#include<string>

class Node
{
	public:
		// Constructor
		Node(Node* lc, Node* rc, std::string v);

		// Copy Constructor
		Node(Node &root);

		// Destructor
		~Node();
		
		// Getters
		Node* left_child();
		Node* right_child();
		std::string value();

		// Getters
		void set_left_child(Node* lc);
		void set_right_child(Node* rc);
		void set_value(int b);

		int node_result();
		std::string node_formula();

	protected:
		Node* left_child_;
		Node* right_child_;
		std::string value_; // operation or operator
};
