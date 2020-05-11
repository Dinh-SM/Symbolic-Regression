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
		Node[] replication(Node parent, int number_of_child);
		Node mutation(Node parent);
		Node * fitness (Node[] tableau_enfants_mutes);
			
	
	protected :


}




