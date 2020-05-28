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



//Functions
Node* Evolution::get_parent_node(Node position, Node root)
{
	Node* parent_node = NULL;
	Node* current_node = &root;
	while(current_node != &position){
		if (current_node->left_child() !=NULL){
			parent_node = current_node;
			current_node = current_node->left_child();
		}
		else if(current_node->right_child() != NULL){
			parent_node = current_node;
			current_node = current_node->right_child();
		}
	}
	return parent_node;
};

	/*Evolution*/
Node* Evolution::replication(Node root, int number_of_child)
{
	
	return 0;
};

void Evolution::mutation(Node position, Node root)
{
	Node* parent = get_parent_node(position, root);
	int prob = rand() % 3; //Normalement (j'ai dit normalement), produit un entier compris entre 0 et 2
	//Selon la probabilité, le node position est copié et subit une des trois mutations:
	if (prob == 0)
	{
		insertion(position, root);
		std::cout << "insertion" << std::endl;
	}
	else if (prob == 1) 
	{
		deletion(position);
		std::cout << "deletion" << std::endl;
	}
	else if (prob == 2)
	{
		replacement(&position, root);
		std::cout << "replacement" << std::endl;
	};
};

/*Mutations*/
void Evolution::insertion(Node position, Node parent)
{
	// Node node_cp(position); // creation of a copy of position
	// Node test(NULL, NULL, operand_true);
	// Node or_(&test, &test, operator_or);
	// Node not_(&test, NULL, operator_not);
	// Node and_(&test, &test, operator_and); 
 //    int prob = rand() %3 ; // prob prend la valeur 0, 1 ou 2
	// if(prob==0){
	// 	position = or_;
	// };
	// if(prob==1){
	// 	position = not_;
	// };
 //    if(prob==2){
	// 	position = and_;
	// };
	// deletion(*position.left_child()); // left child of the futur insertion becomes 0 or 1
 //    position.set_right_child(&node_cp) ; // right child of the futur insertion becomes the position node of the begining of this method.
	
	int prob = rand()%3 ; // prob prend la valeur 0, 1 ou 2
	int prob2 = rand()%2; // prob prend la valeur 0 ou 1
	Node one(NULL, NULL, operand_true);
	Node zero(NULL, NULL, operand_false);

	if(parent.left_child() == &position){
		if(prob==0){
			if(prob2 == 0){
				Node node_to_insert(&position, &zero, operator_and);
				parent.set_left_child(&node_to_insert);
			}
			else if(prob2 == 1){
				Node node_to_insert(&position, &one, operator_and);
				parent.set_left_child(&node_to_insert);
			}
		}
		else if(prob==1){
			if(prob2 == 0){
				Node node_to_insert(&position, &zero, operator_or);
				parent.set_left_child(&node_to_insert);
			}
			else if(prob2 == 1){
				Node node_to_insert(&position, &one, operator_or);
				parent.set_left_child(&node_to_insert);
			}
		}
    	else if(prob==2){
			Node node_to_insert(&position, NULL, operator_not);
			parent.set_left_child(&node_to_insert);
		}
	}
	else if(parent.right_child() == &position){
		if(prob==0){
			if(prob2 == 0){
				Node node_to_insert(&zero, &position, operator_and);
				parent.set_left_child(&node_to_insert);
			}
			else if(prob2 == 1){
				Node node_to_insert(&one, &position, operator_and);
				parent.set_left_child(&node_to_insert);
			}
		}
		else if(prob==1){
			if(prob2 == 0){
				Node node_to_insert(&zero, &position, operator_or);
				parent.set_left_child(&node_to_insert);
			}
			else if(prob2 == 1){
				Node node_to_insert(&one, &position, operator_or);
				parent.set_left_child(&node_to_insert);
			}
		}
    	else if(prob==2){
			Node node_to_insert(&position, NULL, operator_not);
			parent.set_left_child(&node_to_insert);
		}
	}
};

void Evolution::deletion(Node position)
{
	Node * node_current = &position;
	Node * node_p = &position;
	while(position.left_child()!=NULL || position.right_child()!=NULL){
		//std::cout<<"entree boucle while"<<'\n';
		if (node_current->left_child() !=NULL){//le but, c'est d'aller à gauche jusqu'à ce quon tombe sur une feuille
			//std::cout<<"if 1"<<"       ";
			node_p = node_current;
			node_current = node_current->left_child();
		}
		else if(node_current->right_child() != NULL){//après, on regarde l'enfant à droite si il est null ou pas
			//std::cout<<"else if"<<"       ";
			node_p = node_current;
			node_current = node_current->right_child();
		}
		else{
			//std::cout<<"else"<<"           ";
			node_current = node_p;//on remonte
			if(node_current->left_child()!=NULL){
				delete node_current->left_child();
				node_current->set_left_child(NULL);	
				//std::cout<<"delete left"<<"         ";
			}else if(node_current->right_child()!=NULL){
				delete node_current->right_child();
				node_current->set_right_child(NULL);
				//std::cout<<"delete right"<<"         ";
				node_p= &position; //on remonte au noeud muté (consommateur de temps et de ressources mais sûr)
			}
			
		}
	}
	
	int a = rand() % 2;
	std::cout<<"value taken :"<<a<<'\n';
	if (a==0){
		position.set_value(operand_true);	
	}else{
		position.set_value(operand_false);
	}
	/*if (position.left_child()==NULL && position.right_child()==NULL){
	
	}else if (position.left_child()==NULL && position.right_child()!=NULL){
	}else if(position.left_child!=NULL && position.right_child()==NULL){
	}else{
	}*/
};


void Evolution::replacement(Node* position, Node root)
{

	Node node_true(NULL, NULL, operand_true);
	Node node_false(NULL, NULL, operand_true);

//Differenciation entre feuille et noeud
	//Feuille
	if ((position -> value() == operand_false) || (position-> value() == operand_true)){
	//Differenciation entre 1 et 0
		//1
		if (position -> value() == operand_true){
			position -> set_value(operand_false);
		}
		//0
		else{
			position -> set_value(operand_true);
		}
	}
	//Noeud
	else{

		int n = rand() % 3;		//choix au hasard de la transformation d'un noeud en noeud
		int f = rand() % 2;		//choix au hasard de la feuille
	
	//Differenciation entre NOT, AND et OR
		//AND
		if (position -> value() != operator_and){
		//Racine ou noeud?
			
			if (position == &root){
			//Differenciation de la modification
				std::cout << "Nous sommes égaux ou pas!" << std::endl;
				//NOT
				if(n){
					position -> set_value(operator_not);
					position -> set_right_child(NULL);
				}
				//OR
				else{
					position -> set_value(operator_or);
				}
			}
			else{
			//Differenciation de la modification
				std::cout << "Nous sommes différents..." << std::endl;
				//NOT
				if(n){
					position -> set_value(operator_not);
					position -> set_right_child(NULL);
				}
				//Feuille
			/*	else if (n == 2){
				//Differenciaton de la valeur de la feuille
					//1
					if(f){
						position -> set_value(operand_true);
						position -> set_left_child(NULL);
					}
					//0
					else {
						position -> set_value(operand_false);
						position -> set_left_child(NULL);
					}
				}*/
				//OR
				else{
					position -> set_value(operator_or);
				}

			}			
		}
		//NOT
		else if(position -> value() == operator_not){		//ATTENTION : il faudra ajouter un noeuds à l’étage suivant  (ereur de segmentation)
		//Racine ou noeud?
			if (position != &root){
			//Differenciation de la modification
				std::cout << "Nous sommes égaux ou pas!" << std::endl;
				//Or
				if(n){
					position -> set_value(operator_or);
					position -> set_right_child(&node_true);
				
				}
				//And
				else{
					position -> set_value(operator_and);
					position -> set_right_child(&node_true);
				}
			}
			else{
			//Differenciation de la modification
				std::cout << "Nous sommes différents..." << std::endl;
				//Or
				if(n){
					position -> set_value(operator_or);
					position -> set_right_child(&node_true);
				
				}
				//Feuille
/*				else if (n == 2){
				//Differenciaton de la valeur de la feuille
					//1
					if(f){
						position -> set_value(operand_true);
						position -> set_left_child(NULL);
					}
					//0
					else {
						position -> set_value(operand_false);
						position -> set_left_child(NULL);
					}
				}*/
				//And
				else{
					position -> set_value(operator_and);
					position -> set_right_child(&node_true);
				}

			}
		}
		//OR
		else{
		//Racine ou noeud?

			if (position != &root){
			//Differenciation de la modification
				std::cout << "Nous sommes égaux ou pas!" << std::endl;
				//AND
				if(n){
					position -> set_value(operator_and);
				}
				//NOT
				else{
					position -> set_value(operator_not);
					position -> set_right_child(NULL);
				}
			}
			else{
			//Differenciation de la modification
				std::cout << "Nous sommes différents..." << std::endl;
				//And
				if(n){
					position -> set_value(operator_and);
				}
				//Feuille
			/*	else if (n == 2){
				//Differenciation de la feuille
					//1
					if(f){
						position -> set_value(operand_true);
						position -> set_right_child(NULL);
						position -> set_left_child(NULL);
					}
					//0
					else {
						position -> set_value(operand_false);
						position -> set_right_child(NULL);
						position -> set_left_child(NULL);
					}
				}*/
				//NOT
				else{
					position -> set_value(operator_not);
					position -> set_right_child(NULL);
				}
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






