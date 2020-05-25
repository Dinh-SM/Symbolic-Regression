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
	//Selon la probabilité, le node position est copié et subit une des trois mutations:
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
	Node Node_cp(position); // creation of a copy of position
	Node test(NULL, NULL, operand_true);
	Node OR(&test,&test, "OR");
	Node NOT(&test,&test, "NOT");
	Node AND(&test,&test, "AND");
    
    int Prob = rand() %3 ; // Prob prend la valeur 0, 1 ou 2
	if(Prob==0){
		position = OR;
	};
	if(Prob==1){
		position = NOT;
	};
    if(Prob==2){
		position = AND;
	};

	position.left_child()->deletion; // left child of the futur insertion becomes 0 or 1
    position.right_child() = Node_cp; // right child of the futur insertion becomes the position node of the begining of this method.
	
	return empty;
};

Node Evolution::deletion(Node position, Node root)
{
	Node * node_current = &position;
	Node * node_p = &position;
	while(position.left_child()!=NULL || position.right_child()!=NULL){
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
				node_p=parent; //on remonte au noeud muté (consommateur de temps et de ressources mais sur)
			}
			
		}
	}
	
	int a = rand() % 2;
	std::cout<<"value taken :"<<a<<'\n';

	position.set_value(a);	

	/*if (position.left_child()==NULL && position.right_child()==NULL){
	
	}else if (position.left_child()==NULL && position.right_child()!=NULL){
	}else if(position.left_child!=NULL && position.right_child()==NULL){
	}else{
	}*/
	return empty;
};

Node Evolution::replacement(Node position, Node root)
{
	Node children();

if ((position == operand_false) || (position == operand_true)){
	
	if (position == operand_true){
		return children = operand_false;
	}
	else{
		return children = operand_true;
	}
}

else{

	int n = random(0,1);
	
	if (position == operator_and){
		if(n){
			return children = operator_not;		//ATTENTION : il faudra retirer l’un des noeuds suivants
		}
		else{
			return children = operator_or;
		}
	}
	else if(position == operator_not){		//ATTENTION : il faudra ajouter un noeuds à l’étage suivant
		if(n){
			return children = operator_or;
		}
		else{
			return children = operator_and;
		}
	}
	else{
		if(n){
			return children = operator_and;
		}
		else{
			return children = operator_not;		//ATTENTION : il faudra retirer l’un des noeuds suivants
		}
	}
}
};

	/*Fitness*/
int Evolution::fitness(Node tree, int* donnee)
{
	int lenght = sizeof(donnee);
	int fit = 0;

	for ( int i = 0; i < lenght; i++){
		fit += abs(tree.Node::node_result(/*val1[i], val2[i]*/) - donnee[ i ]);
	}
	return -fit;
	
};

Node Evolution::comparative_fitness (Node root, Node* children_tab, int number_of_child, int* donnee)
{
	int fit, new_fit, best;
	
	fit = fitness(root, donnee);
	best = number_of_child;

	for ( int i = 0; i < number_of_child; i++){
		new_fit = fitness(children_tab[ i ], donnee);
		if (new_fit < fit){
			fit = new_fit;
			best = i;
		}
	}

	if (best == number_of_child){
		return root;
	}
	else{
		return children_tab[best];
	}
};


