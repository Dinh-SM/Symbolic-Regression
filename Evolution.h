#include "Node.cpp"

class Evolution 
{
	public :
		//Constructor
		Evolution(Node* node, std::string data);

		//Functions
		std::vector<float> evolution(int number_of_cycles, int number_of_children); // starts the whole algorithm of symbolic regression

		//Getters
		Node* root(); // returns the current base Node of the future mutants
		std::vector<Node*> mutant_children(); // returns the vector of mutants
		std::vector<std::vector<int>> data(); // returns the vector containing the data of the csv file
		std::vector<float> fitnesses(); // returns the vector of computed fitnesses per mutants

		//Setters
		void set_node(Node* node); // changes the base Node of the future mutants
		void set_data(std::string data); // changes the csv file
			
	
	protected :
		std::vector<Node*> replication_(int number_of_children); // makes a vector of clones from the base Node
		void mutation_(Node* position, Node* root, int id); // makes a mutation on a future mutant

			/*Mutations*/
		void insertion_(Node* position, Node* parent, int id); // makes a mutation of type insertion on a future mutant
		void deletion_(Node* position, Node* parent, int id); // makes a mutation of type deletion on a future mutant
		void replacement_(Node* position, Node* parent, int id); // makes a mutation of type replacement on a future mutant
		void replacement_leaf_management_(Node* position, Node* parent, Node* new_node_1, Node* new_node_2,
											int index_1, int index_2, int n, int id); // auxiliary function to manage a replacement on a leaf Node
		void replacement_and_management_(Node* position, Node* parent, Node* new_node_1, Node* new_node_2,
											int index_1, int index_2, int n, int id); // auxiliary function to manage a replacement on an AND Node
		void replacement_or_management_(Node* position, Node* parent, Node* new_node_1, Node* new_node_2,
											int index_1, int index_2, int n, int id); // auxiliary function to manage a replacement on an OR Node
		void replacement_not_management_(Node* position, Node* parent, Node* new_node_1, Node* new_node_2,
											int index_1, int index_2, int n, int id); // auxiliary function to manage a replacement on a NOT Node

			/*Fitness*/
		float compute_fitness_(Node* node); // computes and returns the fitness for one Node
		void compare_fitness_(); // compares all mutants fitnesses and if one of them has a better fitness than the base Node, it becomes the new base Node for the following cycle

		void apoptosis_(Node* node, int id); // deletes a Node with its children
		Node* get_parent_node_(Node* position, Node* root); // returns a pointer pointing on the parent of the Node position
		int left_or_right_child_(Node* position, Node* parent); // returns -1 if the Node position isn't a child, 0 if the Node position is a left child and 1 if the Node position is a right child
		
		Node* node_at_path_(Node* node, std::string path); // returns the Node on which the mutation will occur
		std::string generate_path_(); // generates and returns a randomly generated path to the Node on which the mutation will occur
		
		std::vector<std::vector<int>> parse_data_(std::string data_to_parse); // generates and returns a vector containing the data of the csv file
		
		void generate_used_operands_(Node* root, std::vector<std::string> &sub_used_operands); // generates a vector of vector of unusable genes for each future mutant (only one copy of the gene for one formula)
		void generate_operands_(int number); // generates a vector of vector of usable genes for each future mutant
		void operands_to_used_(int index, int id); // when a gene is used, it is transfered to the corresponding vector of no more usable genes
		void used_to_operands_(int index, int id); // when a Node is deleted, its genes are transfered to the corresponding vector of usable genes
		void re_operands_to_used_(Node* node, int id); // same as operands_to_used_ but with a Node as parameter

		std::vector<Node*> mutant_children_; // vector of mutated clones
		Node* root_; // base Node from which will be generated the clones to be mutated
		std::string path_; // the path to the Node to mutate
		std::vector<std::vector<int>> data_; // vector containing the data of the csv file
		std::vector<float> fitnesses_; // vector of computed fitnesses per mutants
};




