# Symbolic-Regression
	Goal : Find the best approximation
	Content : 2 class --> Node : Treat the tree of the formula
			  --> Evolution : Modify the function


- Node : 3 attributs (2 Node and 1 char*) - include string and vector
	- Public :
		- Constructor : Node(Node* lc, Node* rc, std::string v), copy constructor and destructor
		- Getters 
			- Node* left_child()
			- Node* right_child()
			- std::string value()
		- Setters
			- void set_left_child (Node* lc)
			- void set_right_child (Node* rc)
			- void set_value (std::string s)
		- int node_result(std::vector<int> x) : for have the result of the formula with different value at the end of the tree
		- std::string node_formula() : give the formula of the tree
	- Protected (attributes):
		- Node* left_child_
		- Node* right_child_
		- std::string value_

- Evolution : n attributs () - Use class Node
	- Node* replication(Node root, int number_of_child) : for create number_of_child children to the parent's formula
	- void mutation(Node position, Node root) : choose a mutation to a given node of the formula
	- Node insertion(Node parent, Node root) : make the mutation 'insertion' at a given place of the formula
	- Node deletion(Node parent, Node root) : make the mutation 'deletion' at a given place of the formula
	- Node replacement(Node parent, Node root) : make the mutation 'deletion' at a given node of the formula
	- int fitness(Node tree, int* donnee) : calculation of the fitness of a formula
	- Node * comparative_fitness (Node root, Node* childre_tab, int number_of_child, int* donnee) : choose the best children of the formula