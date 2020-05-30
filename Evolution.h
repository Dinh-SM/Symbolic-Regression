#include "Node.cpp"
#include <vector>

class Evolution 
{
	public : 
		//Constructor
		Evolution(Node* node, std::string data);

		//Functions
		std::vector<Node*> evolution(int number_of_cycles, int number_of_children);

		//Getters
		Node* root();
		std::vector<Node*> mutant_children();
		std::vector<std::vector<int>> data();
		std::vector<float> fitnesses();

		//Setters
		void set_node(Node* node);
		void set_data(std::string data);
			
	
	protected :
		std::vector<Node*> replication_(int number_of_children);
		void mutation_(Node* position, Node* root, int id);

			/*Mutations*/
		void insertion_(Node* position, Node* parent, int id);
		//void deletion(Node position);
		// Version Michel
		void deletion_(Node* position, Node* parent, int id);
		void replacement_(Node* position, Node* parent, int id);
		void replacement_leaf_management_(Node* position, Node* parent, Node* new_node_1, Node* new_node_2,
												int index_1, int index_2, int n, int id);
		void replacement_and_management_(Node* position, Node* parent, Node* new_node_1, Node* new_node_2,
												int index_1, int index_2, int n, int id);
		void replacement_or_management_(Node* position, Node* parent, Node* new_node_1, Node* new_node_2,
												int index_1, int index_2, int n, int id);
		void replacement_not_management_(Node* position, Node* parent, Node* new_node_1, Node* new_node_2,
												int index_1, int index_2, int n, int id);

			/*Fitness*/
		float compute_fitness_(Node* node);
		void comparate_fitness_();

		void apoptosis_(Node* node, int id);
		Node* get_parent_node_(Node* position, Node* root);
		int left_or_right_child_(Node* position, Node* parent);
		Node* node_at_path_(Node* node, std::string path);
		std::string generate_path_();
		std::vector<std::vector<int>> parse_data_(std::string data_to_parse);
		
		void generate_used_operands_(Node* root, std::vector<std::string> &sub_used_operands);
		void generate_operands_(int number);
		void operands_to_used_(int index, int id);
		void used_to_operands_(int index, int id);
		void reused_to_operands_(Node* node, int id);

		std::vector<Node*> mutant_children_;
		Node* root_;
		std::string path_;
		std::vector<std::vector<int>> data_;
		std::vector<float> fitnesses_;
};




