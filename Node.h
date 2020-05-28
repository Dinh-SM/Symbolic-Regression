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
		void set_value(std::string b);

		//Fonction
		void delete_blood();
		int node_result();
		int node_result(int x1, int x2);
		std::string node_formula();

		//Operator
		bool operator== (const Node* second) const;
		bool operator!= (const Node* second) const;

	protected:
		Node* left_child_;
		Node* right_child_;
		std::string value_; // operation or operator
};
