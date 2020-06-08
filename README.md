# Symbolic-Regression
	Goal : Find the best approximation
	Content : 2 class --> Node : Treat the tree of the formula
			  --> Evolution : Modify the function


- Node : 3 attributs (2 Node* and 1 char*) - include string and vector
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

- Evolution : 5 attributs (1 Node* and 4 char*) - Use class Node
	- Public :
		- Constructor : Evolution(Node* node, std::string data)
		- Getters
			- Node* root()
			- std::vector<Node*> mutant_children()
			- std::vector<std::vector<int>> data()
			- std::vector<float> fitnesses()
		- Setters
			- void set_node(Node* node)
			- void set_data(std::string data)
		- std::vector<float> evolution(int number_of_cycles, int number_of_children)
	- Protected :
		- std::vector<Node*> replication_(int number_of_children) : for create number_of_child children to the parent's formula
		- void mutation_(Node* position, Node* root, int id) : makes a mutation on a precise Node of a future mutant
		- void insertion_(Node* position, Node* parent, int id) : make the mutation 'insertion' at a given place of the formula
		- void deletion_(Node* position, Node* parent, int id) : make the mutation 'deletion' at a given place of the formula
		- void replacement_(Node* position, Node* parent, int id) : make the mutation 'replacement' at a given place of the formula
		- void replacement_leaf_management_(Node* position, Node* parent, Node* new_node_1, Node* new_node_2, int index_1, int index_2, int n, int id) : Auxiliary function to manage a replacement on a leaf Node
		- void replacement_and_management_(Node* position, Node* parent, Node* new_node_1, Node* new_node_2, int index_1, int index_2, int n, int id) : Auxiliary function to manage a replacement on an AND Node
		- void replacement_or_management_(Node* position, Node* parent, Node* new_node_1, Node* new_node_2, int index_1, int index_2, int n, int id) : Auxiliary function to manage a replacement on an OR Node
		- void replacement_not_management_(Node* position, Node* parent, Node* new_node_1, Node* new_node_2, int index_1, int index_2, int n, int id) : Auxiliary function to manage a replacement on a NOT Node
		- float compute_fitness_(Node* node) : Computes and returns the fitness for one Node
		- void compare_fitness_() : Compares all mutants' fitnesses and if one of them has a better fitness than the base Node, it becomes the new base Node for the following cycle
		- void apoptosis_(Node* node, int id) : Deletes a Node with its children
		- Node* get_parent_node_(Node* position, Node* root) : Returns a pointer pointing on the parent of the Node position
		- int left_or_right_child_(Node* position, Node* parent) : Returns -1 if the Node position isn't a child, 0 if the Node position is a left child and 1 if the Node position is a right child
		- Node* node_at_path_(Node* node, std::string path) : Returns the Node on which the mutation will occur
		- std::string generate_path_() : Generates and returns a randomly generated path to the Node on which the mutation will occur
		- std::vector<std::vector<int>> parse_data_(std::string data_to_parse) : Generates and returns a vector containing the data of the csv file
		- void generate_used_operands_(Node* root, std::vector<std::string> &sub_used_operands) : Generates a vector of vector of unusable genes for each future mutant (only one copy of the gene for one formula)
		- void generate_operands_(int number) : Generates a vector of vector of usable genes for each future mutant
		- void operands_to_used_(int index, int id) : When a gene is used, it is transfered to the corresponding vector of no more usable genes
		- void used_to_operands_(int index, int id) : When a Node is deleted, its genes are transfered to the corresponding vector of usable genes
		- void re_operands_to_used_(Node* node, int id) : Same as operands_to_used_ but with a Node as parameter
		- Attributes
			- std::vector<Node*> mutant_children_ : Vector of mutated clones
			- Node* root_ : Base Node from which will be generated the clones to be mutated
			- std::string path_ : The path to the actual Node to mutate
			- std::vector<std::vector<int>> data_ : Vector containing the data of the csv file
			- std::vector<float> fitnesses_ : Vector of computed fitnesses per mutants




