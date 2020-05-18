#include "Evolution.h"
#include<iostream>

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
Node* Evolution::replication(Node root, int number_of_child)
{
	
	return 0;
};

void Evolution::mutation(Node position, Node root)
{
	int prob = rand() % 3; //Normalement (j'ai dit normalement), produit un entier compris entre 0 et 2
	//Selon la probabilité, le node parent est copié et subit une des trois mutations:
	if (prob == 0)
	{
		insertion(position, root);
		std::cout << "insertion" << std::endl;
	}
	else if (prob == 1) 
	{
		deletion(position, root);
		std::cout << "deletion" << std::endl;
	}
	else if (prob == 2)
	{
		replacement(position, root);
		std::cout << "replacement" << std::endl;
	};
};

	/*Mutations*/
Node Evolution::insertion(Node position, Node root)
{
	return empty;
};

Node Evolution::deletion(Node position, Node root)
{
	return empty;
};

Node Evolution::replacement(Node position, Node root)
{
	return empty;
};

	/*Fitness*/
int Evolution::fitness(Node tree[])
{
	return 0;
};

Node* Evolution::comparative_fitness (Node* children_tab, int number_of_child)
{
	return &empty;
};


