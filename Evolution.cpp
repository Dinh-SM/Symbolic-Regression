#include "Evolution.h"

//Constructor
Evolution::Evolution()
{

};


//Destructor
Evolution::~Evolution()
{

};


// Getters


//Useful
std::string operand_true("1");
std::string operand_false("0");
std::string operator_or("OR");
std::string operator_and("AND");
std::string operator_not("NOT");
Node empty(NULL, NULL, operand_false);

//Functions

	/*Evolution*/
Node* Evolution::replication(Node parent_tree [], int number_of_child)
{
	
	return 0;
};

void Evolution::mutation(Node parent, Node parent_tree [])
{
	int prob = rand() % 3; //Normalement (j'ai dit normalement), produit un entier compris entre 0 et 2
	//Selon la probabilité, le node parent est copié et subit une des trois mutations:
	if (prob = 0)
	{
		insertion(parent, parent_tree);
	 }
	else if (prob = 1) 
	{
		deletion(parent, parent_tree);
	 }
	else if (prob = 2)
	{
		replacement(parent);
	 };
};

	/*Mutations*/
Node Evolution::insertion(Node parent, Node parent_tree[])
{
	return empty;
};

Node Evolution::deletion(Node parent, Node parent_tree[])
{
	return empty;
};

Node Evolution::replacement(Node parent)
{
	return empty;
};

	/*Fitness*/
int Evolution::fitness(Node tree[ ])
{
	return 0;
};

<<<<<<< HEAD
Node * Evolution::comparative_fitness (Node[] children_tab, int number_of_child)
=======
Node* Evolution::comparative_fitness (Node* children_tab, int number_of_child)
>>>>>>> af3d2e3a2a6a6aca15951768024671eec514de94
{
	return &empty;
};


