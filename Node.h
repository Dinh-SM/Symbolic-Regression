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

		// Setters
		void set_left_child(Node* lc);
		void set_right_child(Node* rc);
		void set_value(int b);

		//Fonction
		int node_result();
		int node_result(int x1, int x2);
		std::string node_formula();

	protected:
		Node* left_child_;
		Node* right_child_;
		std::string value_; // operation or operator
};
