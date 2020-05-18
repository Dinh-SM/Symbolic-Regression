#include "Evolution.h"
#include "Node.cpp"

Node* Node::left_child()
{
	return left_child_;
};

//Constructor
Evolution::Evolution()
{

};


//Destructor
Evolution::~Evolution()
{

};


// Getters



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
	return 0;
};

Node Evolution::deletion(Node parent, Node parent_tree[])
{
	return 0;
};

Node Evolution::replacement(Node parent)
{
	return 0;
};

	/*Fitness*/
int Evolution::fitness(Node tree[ ])
{
	return 0;
};

Node* Evolution::comparative_fitness (Node[] childre_tab, int number_of_child)
{
	return 0;
};


