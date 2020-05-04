class Node
{
	public:
		// Constructor
		Node(Node left_child, Node right_child, value);

		// Destructor
		~Node();
		
		// Getters
		Node left_child();
		Node right_child();
		char* value();

	protected:
		Node left_child_;
		Node right_child_;
		char* value_; // operation or operator
}