#include "Node.cpp"

class Evolution 
{
	public :
		// Constructor
		//! Instantiates an Evolution object with a base Node node and a path to a csv file 
		Evolution(Node* node, std::string data);

		// Functions
		//! Starts the whole algorithm of symbolic regression with number_of_cycles cycles and number_of_children children for each cycle
		std::vector<float> evolution(int number_of_cycles, int number_of_children);

		// Getters
		//! Returns the current base Node of the future mutants
		Node* root();

		//! Returns the vector of mutants
		std::vector<Node*> mutant_children();
		
		//! Returns the vector containing the data of the csv file
		std::vector<std::vector<int>> data();
		
		//! Returns the vector of computed fitnesses per mutants
		std::vector<float> fitnesses();

		// Setters
		//! Changes the base Node of the future mutants
		void set_node(Node* node);
		
		//! Changes the csv file
		void set_data(std::string data);

	
	protected :
		//! Makes a vector of number_of_children clones from the base Node
		std::vector<Node*> replication_(int number_of_children);
		
		//! Makes a mutation on a precise Node of a future mutant
		void mutation_(Node* position, Node* root, int id);

			/*Mutations*/
		//! Makes a mutation of type insertion on a precise Node of a future mutant
		void insertion_(Node* position, Node* parent, int id);
		
		//! Makes a mutation of type deletion on a precise Node of a future mutant
		void deletion_(Node* position, Node* parent, int id);

		//! Makes a mutation of type replacement on a precise Node of a future mutant
		void replacement_(Node* position, Node* parent, int id);

		//! Auxiliary function to manage a replacement on a leaf Node
		void replacement_leaf_management_(Node* position, Node* parent, Node* new_node_1, Node* new_node_2,
											int index_1, int index_2, int n, int id);

		//! Auxiliary function to manage a replacement on an AND Node
		void replacement_and_management_(Node* position, Node* parent, Node* new_node_1, Node* new_node_2,
											int index_1, int index_2, int n, int id);

		//! Auxiliary function to manage a replacement on an OR Node
		void replacement_or_management_(Node* position, Node* parent, Node* new_node_1, Node* new_node_2,
											int index_1, int index_2, int n, int id);

		//! Auxiliary function to manage a replacement on a NOT Node
		void replacement_not_management_(Node* position, Node* parent, Node* new_node_1, Node* new_node_2,
											int index_1, int index_2, int n, int id);

			/*Fitness*/
		//! Computes and returns the fitness for one Node
		float compute_fitness_(Node* node);
		
		//! Compares all mutants' fitnesses and if one of them has a better fitness than the base Node, it becomes the new base Node for the following cycle
		void compare_fitness_();

		//! Deletes a Node with its children
		void apoptosis_(Node* node, int id);
		
		//! Returns a pointer pointing on the parent of the Node position
		Node* get_parent_node_(Node* position, Node* root);

		//! Returns -1 if the Node position isn't a child, 0 if the Node position is a left child and 1 if the Node position is a right child
		int left_or_right_child_(Node* position, Node* parent);
		
		//! Returns the Node on which the mutation will occur
		Node* node_at_path_(Node* node, std::string path);
		
		//! Generates and returns a randomly generated path to the Node on which the mutation will occur
		std::string generate_path_();
		
		//! Generates and returns a vector containing the data of the csv file
		std::vector<std::vector<int>> parse_data_(std::string data_to_parse);
		
		//! Generates a vector of vector of unusable genes for each future mutant (only one copy of the gene for one formula)
		void generate_used_operands_(Node* root, std::vector<std::string> &sub_used_operands);
		
		//! Generates a vector of vector of usable genes for each future mutant
		void generate_operands_(int number);
		
		//! When a gene is used, it is transfered to the corresponding vector of no more usable genes
		void operands_to_used_(int index, int id);
		
		//! When a Node is deleted, its genes are transfered to the corresponding vector of usable genes
		void used_to_operands_(int index, int id);
		
		//! Same as operands_to_used_ but with a Node as parameter
		void re_operands_to_used_(Node* node, int id);

		// Attributes
		std::vector<Node*> mutant_children_; //! Vector of mutated clones
		Node* root_; //! Base Node from which will be generated the clones to be mutated
		std::string path_; //! The path to the actual Node to mutate
		std::vector<std::vector<int>> data_; //! Vector containing the data of the csv file
		std::vector<float> fitnesses_; //! Vector of computed fitnesses per mutants
};




