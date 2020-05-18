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
			/*Evolution*/
		Node* replication(Node root, int number_of_child);
		void mutation(Node position, Node root);

			/*Mutations*/
		Node insertion(Node position, Node root);
		Node deletion(Node position, Node root);
		Node replacement(Node position, Node root);

			/*Fitness*/
		int fitness(Node tree[ ]);
		Node * comparative_fitness (Node* children_tab, int number_of_child);
			
	
	protected :


};




