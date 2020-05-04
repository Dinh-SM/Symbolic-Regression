#include "Node.cpp"

class Evolution 
{
	public : 
		Evolution();
		~Evolution();

		Node[] replication(Node parent, int number_of_child);
		Node mutation(Node parent);
		Node * fitness (Node[] tableau_enfants_mutes);
			
	
	protected :


}




