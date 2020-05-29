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
		std::vector<Node*> mutant_children();
		std::vector<std::vector<int>> data();

		//Setters
		void set_node(Node* node);
			
	
	protected :
		std::vector<Node*> replication_(int number_of_children);
		void mutation_(Node* position, Node* root);

			/*Mutations*/
		void insertion_(Node* position, Node* parent);
		//void deletion(Node position);
		// Version Michel
		void deletion_(Node* position, Node* parent);
		void replacement_(Node* position);

			/*Fitness*/
		int fitness_(int* donnee);
		Node comparate_fitness_(Node* children_tab, int number_of_children, int* donnee);

		void apoptosis_(Node* node);
		Node* get_parent_node_(Node* position, Node* root);
		int left_or_right_child_(Node* position, Node* parent);
		Node* node_at_path_(Node* node, std::string path);
		std::string generate_path_();
		std::vector<std::vector<int>> parse_data_(std::string data_to_parse);
		void generate_operands_();

		std::vector<Node*> mutant_children_;
		Node* root_;
		std::string path_;
		std::vector<std::vector<int>> data_;
};




