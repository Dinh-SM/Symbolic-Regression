#include "Node.cpp"
#include <vector>

class Evolution 
{
	public : 
		//Constructor
		Evolution(Node* node);

		//Functions
		Node* evolution(int number_of_cycles, int number_of_children);
			
	
	protected :
		std::vector<Node*> replication_(int number_of_children);
		void mutation_(Node* position);

			/*Mutations*/
		void insertion_(Node* position, Node* parent);
		//void deletion(Node position);
		// Version Michel
		void deletion_(Node* position, Node* parent);
		void replacement_(Node* position);

			/*Fitness*/
		int fitness_(int* donnee);
		Node comparate_fitness_(Node* children_tab, int number_of_children, int* donnee);

		void delete_tree_(Node* node);
		Node* get_parent_node_(Node* position);
		int left_or_right_child_(Node* position, Node* parent);

		std::vector<Node*> mutant_children;
		Node* root_;

};




