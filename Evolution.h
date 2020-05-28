#include "Node.cpp"
#include <vector>

class Evolution 
{
	public : 
		//Constructor
		Evolution();

		//Functions
			/*Evolution*/
		std::vector<Node*> replication(Node* root, int number_of_children);
		void mutation(Node* position, Node* root);

			/*Mutations*/
		void insertion(Node* position, Node* parent);
		//void deletion(Node position);
		// Version Michel
		void deletion(Node* position, Node* parent);
		void replacement(Node* position, Node root);

			/*Fitness*/
		int fitness(Node tree, int* donnee);
		Node comparative_fitness (Node root, Node* children_tab, int number_of_children, int* donnee);
			
	
	protected :
		void delete_tree_(Node* node);
		Node* get_parent_node_(Node* position, Node* root);
		int left_or_right_child_(Node* position, Node* parent);

};




