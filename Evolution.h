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
		Node[] replication(Node parent_tree [], int number_of_child);
		Node mutation(Node parent, Node parent_tree []);

			/*Mutations*/
		Node insertion(Node parent, Node parent_tree[]);
		Node deletion(Node parent, Node parent_tree[]);
		Node replacement(Node parent);

			/*Fitness*/
		int fitness(Node tree[ ]);
		Node * comparative_fitness (Node[] childre_tab, int number_of_child);
			
	
	protected :


}




