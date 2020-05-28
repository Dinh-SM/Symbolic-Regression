#include "Evolution.h"
#include<iostream>

//Constants, variables
const std::string operand_x1("x1");
const std::string operand_x2("x2");
const std::string operator_or("OR");
const std::string operator_and("AND");
const std::string operator_not("NOT");
Node empty(NULL, NULL, operand_x2);

//Constructor
Evolution::Evolution(Node* node)
{
	root_ = node;
};

//Functions
Node* Evolution::get_parent_node_(Node* position)
{
	Node* parent_node = NULL;
	Node* current_node = root_;
	while(current_node != position){
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

// returns 0 if left_child or 1 if right_child, -1 if neither (error)
int Evolution::left_or_right_child_(Node* position, Node* parent)
{
	if(parent->left_child() == position)
	{
		return 0;
	}
	else if(parent->right_child() == position)
	{
		return 1;
	}

	return -1;
};

void Evolution::delete_tree_(Node* node)
{
	if(node == NULL)
	{
		return;
	}

	if(node->left_child() != NULL)
	{
		delete_tree_(node->left_child());
	}
	else if(node->right_child() != NULL)
	{
		delete_tree_(node->right_child());
	}

	delete node;
};

	/*Evolution*/

Node* Evolution::evolution(int number_of_cycles, int number_of_children)
{
	return NULL;
};

std::vector<Node*> Evolution::replication_(int number_of_children)
{
	std::vector<Node*> children;
	for(int i = 0; i < number_of_children; ++i)
	{
		Node* child = new Node(*root_);
		children.push_back(child);
	}
	return children;
};

void Evolution::mutation_(Node* position)
{
	Node* parent = get_parent_node_(position);

	srand(time(NULL));
	int prob = rand() % 3; //Normalement (j'ai dit normalement), produit un entier compris entre 0 et 2
	//Selon la probabilité, le node position est copié et subit une des trois mutations:
	if (prob == 0)
	{
		insertion_(position, parent);
		std::cout << "INSERTION" << std::endl;
	}
	else if (prob == 1)
	{
		deletion_(position, parent);
		std::cout << "DELETION" << std::endl;
	}
	else if (prob == 2)
	{
		replacement_(position);
		std::cout << "REPLACEMENT" << std::endl;
	};
};

/*Mutations*/
void Evolution::insertion_(Node* position, Node* parent)
{
	srand(time(NULL));
	int prob = rand()%3 ; // prob prend la valeur 0, 1 ou 2
	srand(time(NULL));
	int prob2 = rand()%2; // prob prend la valeur 0 ou 1
	Node* x1 = new Node(NULL, NULL, operand_x1);
	Node* x2 = new Node(NULL, NULL, operand_x2);

	int lr = left_or_right_child_(position, parent);
	if(lr == 0){
		if(prob==0){
			if(prob2 == 0){
				Node* node_to_insert = new Node(position, x2, operator_and);
				parent->set_left_child(node_to_insert);
			}
			else if(prob2 == 1){
				Node* node_to_insert = new Node(position, x1, operator_and);
				parent->set_left_child(node_to_insert);
			}
		}
		else if(prob==1){
			if(prob2 == 0){
				Node* node_to_insert = new Node(position, x2, operator_or);
				parent->set_left_child(node_to_insert);
			}
			else if(prob2 == 1){
				Node* node_to_insert = new Node(position, x1, operator_or);
				parent->set_left_child(node_to_insert);
			}
		}
    	else if(prob==2){
			Node* node_to_insert = new Node(position, NULL, operator_not);
			parent->set_left_child(node_to_insert);
		}
	}
	else if(lr == 1){
		if(prob==0){
			if(prob2 == 0){
				Node* node_to_insert = new Node(x2, position, operator_and);
				parent->set_right_child(node_to_insert);
			}
			else if(prob2 == 1){
				Node* node_to_insert = new Node(x1, position, operator_and);
				parent->set_right_child(node_to_insert);
			}
		}
		else if(prob==1){
			if(prob2 == 0){
				Node* node_to_insert = new Node(x2, position, operator_or);
				parent->set_right_child(node_to_insert);
			}
			else if(prob2 == 1){
				Node* node_to_insert = new Node(x1, position, operator_or);
				parent->set_right_child(node_to_insert);
			}
		}
    	else if(prob==2){
			Node* node_to_insert = new Node(position, NULL, operator_not);
			parent->set_right_child(node_to_insert);
		}
	}
	else
	{
		std::cout << "Error: maybe not corresponding parent-child nodes" << std::endl;
	}
};

/*
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
		position.set_value(operand_x1);	
	}else{
		position.set_value(operand_x2);
	}
	if (position.left_child()==NULL && position.right_child()==NULL){
	
	}else if (position.left_child()==NULL && position.right_child()!=NULL){
	}else if(position.left_child!=NULL && position.right_child()==NULL){
	}else{
	}
};*/

// Version Michel
void Evolution::deletion_(Node* position, Node* parent)
{
	Node* new_node;
	srand(time(NULL));
	int a = rand() % 2;
	if(a == 0)
	{
		new_node = new Node(NULL, NULL, operand_x1);
	}
	else
	{
		new_node = new Node(NULL, NULL, operand_x2);
	}

	int lr = left_or_right_child_(position, parent);
	if(lr == 0)
	{
		delete_tree_(parent->left_child());
		parent->set_left_child(new_node);
	}
	else if(lr == 1)
	{
		delete_tree_(parent->right_child());
		parent->set_right_child(new_node);
	}
	else
	{
		std::cout << "Error: maybe not corresponding parent-child nodes" << std::endl;
	}
};

void Evolution::replacement_(Node* position)
{

	Node* node_true = new Node(NULL, NULL, operand_x1);
	Node* node_false = new Node(NULL, NULL, operand_x1);

	srand(time(NULL));
	int n = rand() % 4;

	//choix au hasard de la transformation d'un noeud en noeud
	int fd = rand() % 2;		//choix au hasard de la feuille de droite

	srand(time(NULL));
	int fg = rand() % 2;		//choix au hasard de la feuille de gauche

	std::cout << n << fd << fg << std::endl;

//Differenciation entre feuille et noeud
	//Feuille
	if((position->value().compare(operand_x2) == 0) 
		|| (position->value().compare(operand_x1) == 0))
	{
	//Differenciation entre 1 et 0
		//1
		if(position->value().compare(operand_x1) == 0)
		{
		//Diferenciation de la modification
			//And
			if(n == 1)
			{
				position -> set_value(operator_and);
			//Differenciaton de la valeur de la feuille droite ajoutée
				//1
				if(fd)
				{
					position -> set_right_child(new Node(*node_true));
				}
				//0
				else
				{
					position -> set_right_child(new Node(*node_false));
				}
			//Differenciaton de la valeur de la feuille gauche ajoutée
				//1
				if(fg)
				{
					position -> set_left_child(new Node(*node_true));
				}
				//0
				else
				{
					position -> set_left_child(new Node(*node_false));
				}
			}
			//Or
			else if(n == 2)
			{
				position -> set_value(operator_or);
			//Differenciaton de la valeur de la feuille droite ajoutée
				//1
				if(fd)
				{
					position -> set_right_child(new Node(*node_true));
				}
				//0
				else
				{
					position -> set_right_child(new Node(*node_false));
				}
			//Differenciaton de la valeur de la feuille gauche ajoutée
				//1
				if(fg)
				{
					position -> set_left_child(new Node(*node_true));
				}
				//0
				else
				{
					position -> set_left_child(new Node(*node_false));
				}
			}
			//Feuille
			else if(n == 3)
			{
				position -> set_value(operand_x2);

				if(position->left_child() != NULL)
				{
					delete_tree_(position->left_child());
					position -> set_left_child(NULL);
				}

				if(position->right_child() != NULL)
				{
					delete_tree_(position->right_child());
					position -> set_right_child(NULL);
				}
			}
			//Not
			else
			{
				position -> set_value(operator_not);
			//Differenciaton de la valeur de la feuille gauche ajoutée
				//1
				if(fg)
				{
					position -> set_left_child(new Node(*node_true));
				}
				//0
				else
				{
					position -> set_left_child(new Node(*node_false));
				}

				if(position->right_child() != NULL)
				{
					delete_tree_(position->right_child());
					position -> set_right_child(NULL);
				}
			}
		}

		//0
		else
		{
		//Diferenciation de la modification
			//And
			if(n == 1)
			{
				position -> set_value(operator_and);
			//Differenciaton de la valeur de la feuille droite ajoutée
				//1
				if(fd)
				{
					position -> set_right_child(new Node(*node_true));
				}
				//0
				else
				{
					position -> set_right_child(new Node(*node_false));
				}
			//Differenciaton de la valeur de la feuille gauche ajoutée
				//1
				if(fg)
				{
					position -> set_left_child(new Node(*node_true));
				}
				//0
				else
				{
					position -> set_left_child(new Node(*node_false));
				}
			}
			//Or
			else if(n == 2)
			{
				position -> set_value(operator_or);
			//Differenciaton de la valeur de la feuille droite ajoutée
				//1
				if(fd)
				{
					position -> set_right_child(new Node(*node_true));
				}
				//0
				else
				{
					position -> set_right_child(new Node(*node_false));
				}
			//Differenciaton de la valeur de la feuille gauche ajoutée
				//1
				if(fg)
				{
					position -> set_left_child(new Node(*node_true));
				}
				//0
				else
				{
					position -> set_left_child(new Node(*node_false));
				}
			}
			//Feuille
			else if(n == 3)
			{
				position -> set_value(operand_x1);

				if(position->left_child() != NULL)
				{
					delete_tree_(position->left_child());
					position -> set_left_child(NULL);
				}

				if(position->right_child() != NULL)
				{
					delete_tree_(position->right_child());
					position -> set_right_child(NULL);
				}
			}
			//Not
			else
			{
				position -> set_value(operator_not);
			//Differenciaton de la valeur de la feuille gauche ajoutée
				//1
				if(fg)
				{
					position -> set_left_child(new Node(*node_true));
				}
				//0
				else
				{
					position -> set_left_child(new Node(*node_false));
				}

				if(position->right_child() != NULL)
				{
					delete_tree_(position->right_child());
					position -> set_right_child(NULL);
				}
			}
		}
	}

	//Noeud
	else
	{
	//Differenciation entre NOT, AND et OR
		//AND
		if(position->value().compare(operator_and) == 0)
		{
		//Racine ou noeud?
			if(position == root_)
			{
			//Differenciation de la modification
				//NOT
				if(n == 1 || n == 3)
				{
					position -> set_value(operator_not);

					if(fg == fd)
					{
						if(position->right_child() != NULL)
						{
							delete_tree_(position->right_child());
							position -> set_right_child(NULL);
						}
					}
					else
					{
						position -> set_left_child(new Node(*position->right_child()));

						if(position->right_child() != NULL)
						{
							delete_tree_(position->right_child());
							position -> set_right_child(NULL);
						}
					}
				}
				//OR
				else if(n == 0 || n == 2)
				{
					position -> set_value(operator_or);
				}
			}
			else
			{
			//Differenciation de la modification
				//NOT
				if(n == 1)
				{
					position -> set_value(operator_not);

					if(fg == fd)
					{
						if(position->right_child() != NULL)
						{
							delete_tree_(position->right_child());
							position -> set_right_child(NULL);
						}
					}
					else
					{
						position -> set_left_child(new Node(*position->right_child()));

						if(position->right_child() != NULL)
						{
							delete_tree_(position->right_child());
							position -> set_right_child(NULL);
						}
					}
				}
				//Feuille - 1
				else if (n == 2)
				{
					position -> set_value(operand_x1);

					if(position->left_child() != NULL)
					{
						delete_tree_(position->left_child());
						position -> set_left_child(NULL);
					}

					if(position->right_child() != NULL)
					{
						delete_tree_(position->right_child());
						position -> set_right_child(NULL);
					}
				}
				//Feuille - 0
				else if (n == 3)
				{
					position -> set_value(operand_x2);
					
					if(position->left_child() != NULL)
					{
						delete_tree_(position->left_child());
						position -> set_left_child(NULL);
					}

					if(position->right_child() != NULL)
					{
						delete_tree_(position->right_child());
						position -> set_right_child(NULL);
					}
				}
				//OR
				else
				{
					position -> set_value(operator_or);
				}

			}			
		}
		//NOT
		else if(position->value().compare(operator_not) == 0)
		//ATTENTION : il faudra ajouter un noeuds à l’étage suivant  (ereur de segmentation)
		{
		//Racine ou noeud?
			if(position == root_)
			{
			//Differenciation de la modification
				//Or
				if(n == 1 || n == 3)
				{
					position -> set_value(operator_or);
				//Differenciaton de la valeur de la feuille ajoutée
					//1
					if(fd)
					{
						position -> set_right_child(new Node(*node_true));
					}
					//0
					else
					{
						position -> set_right_child(new Node(*node_false));
					}
				
				}
				//And
				else if(n == 0 || n == 2)
				{
					position -> set_value(operator_and);
				//Differenciaton de la valeur de la feuille ajoutée
					//1
					if(fd)
					{
						position -> set_right_child(new Node(*node_true));
					}
					//0
					else
					{
						position -> set_right_child(new Node(*node_false));
					}
				}
			}
			else
			{
			//Differenciation de la modification
				//Or
				if(n == 1)
				{
					position -> set_value(operator_or);
				//Differenciaton de la valeur de la feuille ajoutée
					//1
					if(fd)
					{
						position -> set_right_child(new Node(*node_true));
					}
					//0
					else
					{
						position -> set_right_child(new Node(*node_false));
					}
				
				}
				//Feuille - 1
				else if (n == 2)
				{
					position -> set_value(operand_x1);

					if(position->left_child() != NULL)
					{
						delete_tree_(position->left_child());
						position -> set_left_child(NULL);
					}
				}
				//Feuille - 0
				else if (n == 3)
				{
					position -> set_value(operand_x2);

					if(position->left_child() != NULL)
					{
						delete_tree_(position->left_child());
						position -> set_left_child(NULL);
					}
				}
				//And
				else
				{
					position -> set_value(operator_and);
				//Differenciaton de la valeur de la feuille ajoutée
					//1
					if(fd)
					{
						position -> set_right_child(new Node(*node_true));
					}
					//0
					else
					{
						position -> set_right_child(new Node(*node_false));
					}
				}

			}
		}

		//OR
		else
		{
		//Racine ou noeud?
			if (position == root_)
			{
			//Differenciation de la modification
				//AND
				if(n == 1 || n == 3)
				{
					position -> set_value(operator_and);
				}
				//NOT
				else if(n == 0 || n == 2)
				{
					position -> set_value(operator_not);

					if(fg == fd)
					{
						if(position->right_child() != NULL)
						{
							delete_tree_(position->right_child());
							position -> set_right_child(NULL);
						}
					}
					else
					{
						position -> set_left_child(new Node(*position->right_child()));

						if(position->right_child() != NULL)
						{
							delete_tree_(position->right_child());
							position -> set_right_child(NULL);
						}
					}
				}
			}
			else
			{
			//Differenciation de la modification
				//And
				if(n == 1)
				{
					position -> set_value(operator_and);
				}
				//Feuille - 1
				else if (n == 2)
				{
					position -> set_value(operand_x1);

					if(position->left_child() != NULL)
					{
						delete_tree_(position->left_child());
						position -> set_left_child(NULL);
					}

					if(position->right_child() != NULL)
					{
						delete_tree_(position->right_child());
						position -> set_right_child(NULL);
					}
				}
				//Feuille - 0
				else if (n == 3)
				{
					position -> set_value(operand_x2);

					if(position->left_child() != NULL)
					{
						delete_tree_(position->left_child());
						position -> set_left_child(NULL);
					}

					if(position->right_child() != NULL)
					{
						delete_tree_(position->right_child());
						position -> set_right_child(NULL);
					}
				}
				//NOT
				else
				{
					position -> set_value(operator_not);

					if(fg == fd)
					{
						if(position->right_child() != NULL)
						{
							delete_tree_(position->right_child());
							position -> set_right_child(NULL);
						}
					}
					else
					{
						position -> set_left_child(new Node(*position->right_child()));

						if(position->right_child() != NULL)
						{
							delete_tree_(position->right_child());
							position -> set_right_child(NULL);
						}
					}
				}
			}
		}
	}
};


/*Fitness*/
int Evolution::fitness_(int* donnee)
{
	//int lenght = sizeof(donnee);
	//int fit = 0;

	//for ( int i = 0; i < lenght; i++){
	//	fit += abs(tree.Node::node_result(/*val1[i], val2[i]*/) - donnee[ i ]);
	//}
	return 0;
	
};

Node Evolution::comparate_fitness_(Node* children_tab, int number_of_children, int* donnee)
{
	/*int fit, new_fit, best;
	
	fit = fitness_(donnee);
	best = number_of_children;

	for ( int i = 0; i < number_of_children; i++){
		new_fit = fitness_(children_tab[ i ], donnee);
		if (new_fit < fit){
			fit = new_fit;
			best = i;
		}
	}

	if (best == number_of_children){
		return *root_;
	}
	else{
		return children_tab[best];
	}*/
	return *root_;
};