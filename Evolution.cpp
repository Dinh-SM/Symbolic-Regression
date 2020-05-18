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
Node* Evolution::replication(Node parent_tree, int number_of_child)
{
	
	return 0;
};

void Evolution::mutation(Node parent, Node parent_tree)
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
Node Evolution::insertion(Node parent, Node parent_tree)
{
	return empty;
};

Node Evolution::deletion(Node parent, Node parent_tree)
{
	Node * node_current = &parent;
	Node * node_p = &parent;
	while(parent.left_child()!=NULL || parent.right_child()!=NULL){
		std::cout<<"entree boucle while"<<'\n';
		if (node_current->left_child() !=NULL){//le but, c'est d'aller à gauche jusqu'à ce quon tombe sur une feuille
			std::cout<<"if 1"<<"       ";
			node_p = node_current;
			node_current = node_current->left_child();
		}
		else if(node_current->right_child() != NULL){//après, on regarde l'enfant à droite si il est null ou pas
			std::cout<<"else if"<<"       ";
			node_p = node_current;
			node_current = node_current->right_child();
		}
		else{
			std::cout<<"else"<<"           ";
			node_current = node_p;//on remonte
			if(node_current->left_child()!=NULL){
				delete node_current->left_child();
				node_current->set_left_child(NULL);	
				std::cout<<"delete left"<<"         ";
			}else if(node_current->right_child()!=NULL){
				delete node_current->right_child();
				node_current->set_right_child(NULL);
				std::cout<<"delete right"<<"         ";
			}
			
		}
	}
	
	int a = rand() % 2;
	std::cout<<"value taken :"<<a<<'\n';

	parent.set_value(a);	

	/*if (parent.left_child()==NULL && parent.right_child()==NULL){
	
	}else if (parent.left_child()==NULL && parent.right_child()!=NULL){
	}else if(parent.left_child!=NULL && parent.right_child()==NULL){
	}else{
	}*/
	return empty;
};

Node Evolution::replacement(Node parent)
{
	return empty;
};

	/*Fitness*/
int Evolution::fitness(Node tree[])
{
	return 0;
};

/*<<<<<<< HEAD
Node * Evolution::comparative_fitness (Node[] children_tab, int number_of_child)
=======*/
Node* Evolution::comparative_fitness (Node* children_tab, int number_of_child)
//>>>>>>> af3d2e3a2a6a6aca15951768024671eec514de94
{
	return &empty;
};


