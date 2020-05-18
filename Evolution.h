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
		Node* replication(Node parent_tree, int number_of_child);
/*<<<<<<< HEAD
		Node mutation(Node parent, Node parent_tree []);
=======*/
		void mutation(Node parent, Node parent_tree);
//>>>>>>> af3d2e3a2a6a6aca15951768024671eec514de94

			/*Mutations*/
		Node insertion(Node parent, Node parent_tree);
		Node deletion(Node parent, Node parent_tree);
		Node replacement(Node parent);

			/*Fitness*/
		int fitness(Node tree[ ]);
/*<<<<<<< HEAD
		Node * comparative_fitness (Node[] children_tab, int number_of_child);
=======*/
		Node * comparative_fitness (Node* children_tab, int number_of_child);
//>>>>>>> af3d2e3a2a6a6aca15951768024671eec514de94
			
	
	protected :


};




