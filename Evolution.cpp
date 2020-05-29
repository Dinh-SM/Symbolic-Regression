#include "Evolution.h"
#include<iostream>
#include<fstream>
#include<sstream>

//Constants, variables
std::vector<std::string> operands;
std::vector<std::string> used_operands;
const std::string operand_x1("x1");
const std::string operand_x2("x2");
const std::string operator_or("OR");
const std::string operator_and("AND");
const std::string operator_not("NOT");

//Constructor
Evolution::Evolution(Node* node, std::string data)
{
	root_ = node;
	data_ = parse_data_(data);
	generate_operands_();
	srand(time(NULL));
};

//Getters
std::vector<Node*> Evolution::mutant_children()
{
	return mutant_children_;
};

std::vector<std::vector<int>> Evolution::data()
{
	return data_;
};

//Setters
void Evolution::set_node(Node* node){
	root_ = node;
	path_ = "";
};

//Functions
Node* Evolution::get_parent_node_(Node* position, Node* root)
{
	if(root->left_child() == position || root->right_child() == position)
	{
		return root;
	}

	Node* n = NULL;

	if (root->left_child() != NULL)
	{
		n = get_parent_node_(position, root->left_child());
	}
	
	if (n != NULL)
	{
		return n;
	}
	
	if (root->right_child() != NULL)
	{
		n = get_parent_node_(position, root->right_child());
	}
	
	if (n != NULL)
	{
		return n;
	}

	return NULL;
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

void Evolution::apoptosis_(Node* node)
{
	if(node == NULL)
	{
		return;
	}

	if(node->left_child() != NULL)
	{
		apoptosis_(node->left_child());
	}
	else if(node->right_child() != NULL)
	{
		apoptosis_(node->right_child());
	}

	delete node;
};

Node* Evolution::node_at_path_(Node* node, std::string path)
{
	Node* current_node = node;
	for (int i = 0; i < path.length(); ++i)
	{
		if(path.c_str()[i] == 'l' && current_node->left_child() != NULL)
		{
			current_node = current_node->left_child();
		}
		else if(path.c_str()[i] == 'r' && current_node->right_child() != NULL)
		{
			current_node = current_node->right_child();
		}
		else
		{
			break;
		}
	}
	return current_node;
};

std::string Evolution::generate_path_()
{
	std::string path("");
	int j = rand()%18+1;
	for (int i = 0; i < j; ++i)
	{
		if(rand()%2)
		{
			path = path + 'l';
		}
		else
		{
			path = path + 'r';
		}
	}
	return path;
};

void Evolution::generate_operands_()
{
	for (int i = 0; i < data_[0].size(); ++i)
	{
		operands.push_back(std::to_string(i+1));
	}
};

	/*Evolution*/
std::vector<Node*> Evolution::evolution(int number_of_cycles, int number_of_children)
{
	mutant_children_ = replication_(number_of_children);

	for (int j = 0; j < number_of_cycles; ++j)
	{
		path_ = generate_path_();
		for (int i = 0; i < number_of_children; ++i)
		{
			mutation_(node_at_path_(mutant_children_[i], path_), mutant_children_[i]);
		}
	}

	return mutant_children_;
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

void Evolution::mutation_(Node* position, Node* root)
{
	Node* parent = get_parent_node_(position, root);
	if(parent == NULL)
	{
		std::cout << "Parent pas trouvé : Mission avortée" << std::endl;
		return;
	}

	int prob = std::rand() % 3; //Normalement (j'ai dit normalement), produit un entier compris entre 0 et 2
	//Selon la probabilité, le node position est copié et subit une des trois mutations:
	if (prob == 0)
	{
		insertion_(position, parent);
	}
	else if (prob == 1)
	{
		deletion_(position, parent);
	}
	else if (prob == 2)
	{
		replacement_(position);
	};
};

/*Mutations*/
void Evolution::insertion_(Node* position, Node* parent)
{
	int prob = rand()%3 ; // prob prend la valeur 0, 1 ou 2
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
	
	int a = std::rand() % 2;
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
	int a = std::rand() % 2;
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
		apoptosis_(parent->left_child());
		parent->set_left_child(new_node);
	}
	else if(lr == 1)
	{
		apoptosis_(parent->right_child());
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

	int n = std::rand() % 4;

	//choix au hasard de la transformation d'un noeud en noeud
	int fd = std::rand() % 2;		//choix au hasard de la feuille de droite

	int fg = std::rand() % 2;		//choix au hasard de la feuille de gauche

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
					apoptosis_(position->left_child());
					position -> set_left_child(NULL);
				}

				if(position->right_child() != NULL)
				{
					apoptosis_(position->right_child());
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
					apoptosis_(position->right_child());
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
					apoptosis_(position->left_child());
					position -> set_left_child(NULL);
				}

				if(position->right_child() != NULL)
				{
					apoptosis_(position->right_child());
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
					apoptosis_(position->right_child());
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
							apoptosis_(position->right_child());
							position -> set_right_child(NULL);
						}
					}
					else
					{
						position -> set_left_child(new Node(*position->right_child()));

						if(position->right_child() != NULL)
						{
							apoptosis_(position->right_child());
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
							apoptosis_(position->right_child());
							position -> set_right_child(NULL);
						}
					}
					else
					{
						position -> set_left_child(new Node(*position->right_child()));

						if(position->right_child() != NULL)
						{
							apoptosis_(position->right_child());
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
						apoptosis_(position->left_child());
						position -> set_left_child(NULL);
					}

					if(position->right_child() != NULL)
					{
						apoptosis_(position->right_child());
						position -> set_right_child(NULL);
					}
				}
				//Feuille - 0
				else if (n == 3)
				{
					position -> set_value(operand_x2);
					
					if(position->left_child() != NULL)
					{
						apoptosis_(position->left_child());
						position -> set_left_child(NULL);
					}

					if(position->right_child() != NULL)
					{
						apoptosis_(position->right_child());
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
						apoptosis_(position->left_child());
						position -> set_left_child(NULL);
					}
				}
				//Feuille - 0
				else if (n == 3)
				{
					position -> set_value(operand_x2);

					if(position->left_child() != NULL)
					{
						apoptosis_(position->left_child());
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
							apoptosis_(position->right_child());
							position -> set_right_child(NULL);
						}
					}
					else
					{
						position -> set_left_child(new Node(*position->right_child()));

						if(position->right_child() != NULL)
						{
							apoptosis_(position->right_child());
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
						apoptosis_(position->left_child());
						position -> set_left_child(NULL);
					}

					if(position->right_child() != NULL)
					{
						apoptosis_(position->right_child());
						position -> set_right_child(NULL);
					}
				}
				//Feuille - 0
				else if (n == 3)
				{
					position -> set_value(operand_x2);

					if(position->left_child() != NULL)
					{
						apoptosis_(position->left_child());
						position -> set_left_child(NULL);
					}

					if(position->right_child() != NULL)
					{
						apoptosis_(position->right_child());
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
							apoptosis_(position->right_child());
							position -> set_right_child(NULL);
						}
					}
					else
					{
						position -> set_left_child(new Node(*position->right_child()));

						if(position->right_child() != NULL)
						{
							apoptosis_(position->right_child());
							position -> set_right_child(NULL);
						}
					}
				}
			}
		}
	}
};

std::vector<std::vector<int>> Evolution::parse_data_(std::string data_to_parse)
{
	std::ifstream  data(data_to_parse);
    std::string line;
	getline(data, line, '\n');
    std::vector<std::vector<int>> parsed_csv;
    while(std::getline(data,line))
    {
        std::stringstream line_stream(line);
        std::string cell;
        getline(line_stream, cell, ',');
        std::vector<int> parsed_row;
        while(std::getline(line_stream,cell,','))
        {
            parsed_row.push_back(std::atoi(cell.c_str()));
        }

        parsed_csv.push_back(parsed_row);
    }

    return parsed_csv;
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