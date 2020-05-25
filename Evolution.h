#include "Node.cpp"

class Evolution 
{
	public : 
		//Constructor
		Evolution();

		//Destructor
		~Evolution();

		// Getters

		//Functions
		Node* get_parent_node(Node position, Node root);

			/*Evolution*/
		Node* replication(Node root, int number_of_child);
		void mutation(Node position, Node root);

			/*Mutations*/
		void insertion(Node position, Node root);
		void deletion(Node position);
		void replacement(Node position, Node root);

			/*Fitness*/
		int fitness(Node tree, int* donnee);
		Node comparative_fitness (Node root, Node* children_tab, int number_of_child, int* donnee);
			
	
	protected :


};




