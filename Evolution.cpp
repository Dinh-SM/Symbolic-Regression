#include "Evolution.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

//Constants, variables
std::vector<std::vector<std::string>> operands;
std::vector<std::vector<std::string>> used_operands;

//Constructor
Evolution::Evolution(Node* node, std::string data)
{
	root_ = node;
	data_ = parse_data_(data);
	srand(time(NULL)); // sets the seed at current time for the randomization
};

//Getters
// returns the current base Node of the future mutants
Node* Evolution::root()
{
	return root_;
};

// returns the vector of mutants
std::vector<Node*> Evolution::mutant_children()
{
	return mutant_children_;
};

// returns the vector containing the data of the csv file
std::vector<std::vector<int>> Evolution::data()
{
	return data_;
};

// returns the vector of computed fitnesses per mutants
std::vector<float> Evolution::fitnesses()
{
	return fitnesses_;
};

//Setters
// changes the base Node of the future mutants
void Evolution::set_node(Node* node){
	root_ = node;
};

// changes the csv file
void Evolution::set_data(std::string data){
	data_ = parse_data_(data);
};

//Functions
// returns a pointer pointing on the parent of the Node position
Node* Evolution::get_parent_node_(Node* position, Node* root)
{
	if(root->left_child() == position || root->right_child() == position) // if one of the child of this Node is the Node position, it means that Node is its parent Node
	{
		return root;
	}

	Node* n = NULL;

	if (root->left_child() != NULL) // if there's a left child, checks the left child
	{
		n = get_parent_node_(position, root->left_child()); // recursive call on the left child
	}
	
	if (n != NULL)
	{
		return n;
	}
	
	if (root->right_child() != NULL) // if there's a right child, checks the right child
	{
		n = get_parent_node_(position, root->right_child()); // recursive call on the right child
	}
	
	if (n != NULL)
	{
		return n;
	}

	return NULL;
};

// returns -1 if the Node position isn't a child, 0 if the Node position is a left child and 1 if the Node position is a right child
int Evolution::left_or_right_child_(Node* position, Node* parent)
{
	if(parent == NULL)
	{
		return -1;
	}
	else if(parent->left_child() == position)
	{
		return 0;
	}
	else if(parent->right_child() == position)
	{
		return 1;
	}

	return -1;
};

// deletes a Node with its children
void Evolution::apoptosis_(Node* node, int id)
{
	if(node == NULL) // stops if the Node is NULL
	{
		return;
	}

	if(node->left_child() != NULL) // if there's a left child, deletes the left child
	{
		apoptosis_(node->left_child(), id); // recursive call on the left child
	}
	
	if(node->right_child() != NULL) // if there's a right child, deletes the right child
	{
		apoptosis_(node->right_child(), id); // recursive call on the right child
	}

	// if the value of the Node to be deleted is a gene, transfer the gene to the corresponding vector of usable genes
	if(node->value().compare(operator_and) != 0
		&& node->value().compare(operator_or) != 0
		&& node->value().compare(operator_not) != 0)
	{
		for (int i = 0; i < used_operands[id].size(); ++i)
		{
			if(node->value().compare(used_operands[id][i]) == 0)
			{
				used_to_operands_(i, id);
				break;
			}
		}
	}

	// Node deletion
	delete node;
};

// returns the Node on which the mutation will occur
Node* Evolution::node_at_path_(Node* node, std::string path)
{
	Node* current_node = node;
	for (int i = 0; i < path.length(); ++i)
	{
		if(path.c_str()[i] == 'l' && current_node->left_child() != NULL) // if path says "l", go to the left
		{
			current_node = current_node->left_child();
		}
		else if(path.c_str()[i] == 'r' && current_node->right_child() != NULL) // if path says "r", go to the right
		{
			current_node = current_node->right_child();
		}
		else // if path says something but you can't do it, stop
		{
			break;
		}
	}

	return current_node;
};

// generates and returns a randomly generated path to the Node on which the mutation will occur
std::string Evolution::generate_path_()
{
	std::string path("");
	int j = rand()%100; // path of random size from 0 to 99
	for (int i = 0; i < j; ++i)
	{
		if(rand()%2) // randomly choses between l for left and r for right
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

// generates a vector of vector of unusable genes for each future mutant (only one copy of the gene for one formula)
void Evolution::generate_used_operands_(Node* root, std::vector<std::string> &sub_used_operands)
{
	// adds the value of the Node to the vector of used genes
	if(root->value().compare(operator_and) != 0
		&& root->value().compare(operator_or) != 0
		&& root->value().compare(operator_not) != 0)
	{
		if(std::find(sub_used_operands.begin(), sub_used_operands.end(), root->value()) == sub_used_operands.end())
		{
			sub_used_operands.push_back(std::string(root->value()));
		}
	}

	if(root->left_child() != NULL)
	{
		generate_used_operands_(root->left_child(), sub_used_operands); // recursive call on left child
	}

	if(root->right_child() != NULL)
	{
		generate_used_operands_(root->right_child(), sub_used_operands); // recursive call on right child
	}

	if(root->left_child() == NULL && root->right_child() == NULL) // if leaf, stops
	{
		return;
	}
};

// generates a vector of vector of usable genes for each future mutant
void Evolution::generate_operands_(int number)
{
	operands.clear(); // resets usable genes
	used_operands.clear(); // resets unusable genes

	// fills the vector of unusable genes for each mutant
	for (int i = 0; i < number; ++i)
	{
		std::vector<std::string> sub_used_operands;
		generate_used_operands_(new Node(*root_), sub_used_operands);
		used_operands.push_back(sub_used_operands);
	}
	
	// fills the vector of usable genes for each mutant
	for (int k = 0; k < number; ++k)
	{
		std::vector<std::string> sub_operands;
		for (int i = 0; i < data_[0].size()-1; ++i)
		{
			if(std::find(used_operands[k].begin(), used_operands[k].end(), std::to_string(i+1)) == used_operands[k].end())
			{
				sub_operands.push_back(std::to_string(i+1));
			}
		}
		operands.push_back(sub_operands);
	}
};

// when a gene is used, it is transfered to the corresponding vector of no more usable genes
void Evolution::operands_to_used_(int index, int id)
{
	used_operands[id].push_back(operands[id][index]);
	operands[id].erase(operands[id].begin()+index);
};

// when a Node is deleted, its genes are transfered to the corresponding vector of usable genes
void Evolution::used_to_operands_(int index, int id)
{
	operands[id].push_back(used_operands[id][index]);
	used_operands[id].erase(used_operands[id].begin()+index);
};

// same as operands_to_used_ but with a Node as parameter
void Evolution::re_operands_to_used_(Node* node, int id)
{
	if(node == NULL)
	{
		return;
	}

	if(node->left_child() != NULL)
	{
		re_operands_to_used_(node->left_child(), id); // recursive call on left child
	}
	
	if(node->right_child() != NULL)
	{
		re_operands_to_used_(node->right_child(), id); // recursive call on right child
	}

	// adds the value of the Node to the vector of unusable genes
	if(node->value().compare(operator_and) != 0
		&& node->value().compare(operator_or) != 0
		&& node->value().compare(operator_not) != 0)
	{
		if(std::find(used_operands[id].begin(), used_operands[id].end(), node->value()) == used_operands[id].end())
		{
			for (int i = operands[id].size()-1; i > 0; --i)
			{
				if(node->value().compare(operands[id][i]) == 0)
				{
					operands_to_used_(i, id);
				}
			}
		}
	}
};

	/*Evolution*/
// starts the whole algorithm of symbolic regression
std::vector<float> Evolution::evolution(int number_of_cycles, int number_of_children)
{
	std::vector<float> fitness_progression;
	fitness_progression.push_back(compute_fitness_(root_));
	for (int j = 0; j < number_of_cycles; ++j)
	{
		mutant_children_ = replication_(number_of_children); // makes the clones of the base Node
		path_ = generate_path_(); // generates the path for this cycle
		generate_operands_(number_of_children); // generates the usable and unusable genes
		fitnesses_.clear(); // resets the vector of fitnesses

		// if the vector of usable genes is empty (all genes were used), stops the process
		if(operands[0].empty())
		{
			break;
		}

		// mutation and fitness computing for each clone
		for (int i = 0; i < number_of_children; ++i)
		{
			mutation_(node_at_path_(mutant_children_[i], path_), mutant_children_[i], i);
			fitnesses_.push_back(compute_fitness_(mutant_children_[i]));
		}

		// compares fitnesses and changes the base Node if necessary
		compare_fitness_();
		fitness_progression.push_back(compute_fitness_(root_));
	}

	// writes the best formula obtained and its fitness at the and of the cycles into a file named "formula.out"
	std::ofstream myfile;
	myfile.open("formula.out", std::ios_base::app);
	myfile << root_->node_formula() << "\t" << compute_fitness_(root_) << std::endl;
	myfile.close();

	return fitness_progression;
};

// makes a vector of clones from the base Node
std::vector<Node*> Evolution::replication_(int number_of_children)
{
	std::vector<Node*> children;
	for(int i = 0; i < number_of_children; ++i)
	{
		Node* child = new Node(*root_); // use of the copy constructor to make independant clones
		children.push_back(child);
	}

	return children;
};

	/*Mutations*/
// makes a mutation on a future mutant
void Evolution::mutation_(Node* position, Node* root, int id)
{
	Node* parent = get_parent_node_(position, root);

	int prob = rand() % 3; //Normalement, produit un entier compris entre 0 et 2
	//Selon la probabilité, le node position subit une des trois mutations:
	if (prob == 0 && position != root)
	{
		insertion_(position, parent, id);
	}
	else if (prob == 1 && position != root)
	{
		deletion_(position, parent, id);
	}
	else if (prob == 2)
	{
		replacement_(position, parent, id);
	}
};

// makes a mutation of type insertion on a future mutant
void Evolution::insertion_(Node* position, Node* parent, int id)
{
	int prob = rand()%3 ; // prob prend la valeur 0, 1 ou 2 pour choisir entre AND, OR et NOT
	int prob2 = rand() % operands[id].size(); // prob2 prend une valeur entre 0 et 118 pour choisir le gène
	
	Node* x = new Node(NULL, NULL, std::string(operands[id][prob2]));

	int lr = left_or_right_child_(position, parent);
	if(lr == 0){
		if(prob==0){
			operands_to_used_(prob2, id);
			Node* node_to_insert = new Node(position, x, operator_and);
			parent->set_left_child(node_to_insert);
		}
		else if(prob==1){
			operands_to_used_(prob2, id);
			Node* node_to_insert = new Node(position, x, operator_or);
			parent->set_left_child(node_to_insert);
		}
    	else if(prob==2){
			Node* node_to_insert = new Node(position, NULL, operator_not);
			parent->set_left_child(node_to_insert);
		}
	}
	else if(lr == 1){
		if(prob==0){
			operands_to_used_(prob2, id);
			Node* node_to_insert = new Node(x, position, operator_and);
			parent->set_right_child(node_to_insert);
		}
		else if(prob==1){
			operands_to_used_(prob2, id);
			Node* node_to_insert = new Node(x, position, operator_or);
			parent->set_right_child(node_to_insert);
		}
    	else if(prob==2){
			Node* node_to_insert = new Node(position, NULL, operator_not);
			parent->set_right_child(node_to_insert);
		}
	}
	else
	{
		std::cout << "Error l.346: maybe not corresponding parent-child nodes" << std::endl;
	}
};

// makes a mutation of type deletion on a future mutant
void Evolution::deletion_(Node* position, Node* parent, int id)
{
	int a = rand() % operands[id].size();
	Node* new_node = new Node(NULL, NULL, std::string(operands[id][a]));
	operands_to_used_(a, id);

	int lr = left_or_right_child_(position, parent);
	if(lr == 0)
	{
		apoptosis_(parent->left_child(), id); // recursive call on left child
		parent->set_left_child(new_node); // node replaced by a leaf which cuts everything underneath
	}
	else if(lr == 1)
	{
		apoptosis_(parent->right_child(), id); // recursive call on right child
		parent->set_right_child(new_node); // node replaced by a leaf which cuts everything underneath
	}
	else
	{
		std::cout << "Error l.419: maybe not corresponding parent-child nodes" << std::endl;
	}
};

// makes a mutation of type replacement on a future mutant
void Evolution::replacement_(Node* position, Node* parent, int id)
{
	int n = rand() % 4;

	//choix au hasard de la transformation d'un noeud en noeud
	int a = -1;
	int b = -1;
	while(a == b){
		a = rand() % operands[id].size();
		b = rand() % operands[id].size();
	}

	Node* new_node_1 = new Node(NULL, NULL, std::string(operands[id][a]));
	Node* new_node_2 = new Node(NULL, NULL, std::string(operands[id][b]));

//Differenciation entre feuille et noeud
	//Feuille
	if(std::find(used_operands[id].begin(), used_operands[id].end(), position->value()) != used_operands[id].end())
	{
		replacement_leaf_management_(position, parent, new_node_1, new_node_2, a, b, n, id);
	}
	else if(position->value().compare(operator_and) == 0)
	{
		replacement_and_management_(position, parent, new_node_1, new_node_2, a, b, n, id);
	}
	else if(position->value().compare(operator_or) == 0)
	{
		replacement_or_management_(position, parent, new_node_1, new_node_2, a, b, n, id);
	}
	else if(position->value().compare(operator_not) == 0)
	{
		replacement_not_management_(position, parent, new_node_1, new_node_2, a, b, n, id);	
	}
};

// auxiliary function to manage a replacement on a leaf Node
void Evolution::replacement_leaf_management_(Node* position, Node* parent, Node* new_node_1, Node* new_node_2,
											int index_1, int index_2, int n, int id)
{
	for (int i = 0; i < used_operands[id].size(); ++i)
	{
		if(position->value().compare(used_operands[id][i]) == 0)
		{
			used_to_operands_(i, id);
			break;
		}
	}

	//Diferenciation de la modification
	//And
	if(n == 1)
	{
		position -> set_value(operator_and);
		
		//Differenciaton de la valeur de la feuille droite ajoutée
		position -> set_right_child(new_node_1);
		operands_to_used_(index_1, id);
		
		//Differenciaton de la valeur de la feuille gauche ajoutée
		position -> set_left_child(new_node_2);
		if(index_1 > index_2)
		{
			operands_to_used_(index_2, id);
		}
		else
		{
			operands_to_used_(index_2-1, id);
		}
	}

	//Or
	else if(n == 2)
	{
		position -> set_value(operator_or);
		
		//Differenciaton de la valeur de la feuille droite ajoutée
		position -> set_right_child(new_node_1);
		operands_to_used_(index_1, id);
		
		//Differenciaton de la valeur de la feuille gauche ajoutée
		position -> set_left_child(new_node_2);
		if(index_1 > index_2)
		{
			operands_to_used_(index_2, id);
		}
		else
		{
			operands_to_used_(index_2-1, id);
		}
	}

	//Feuille
	else if(n == 3)
	{
		int randomizer = rand() % 2;

		int lr = left_or_right_child_(position, parent);
		if(lr == 0)
		{
			if(randomizer == 0)
			{
				operands_to_used_(index_1, id);
				apoptosis_(parent->left_child(), id);
				parent->set_left_child(new_node_1);
			}
			else
			{
				operands_to_used_(index_2, id);
				apoptosis_(parent->left_child(), id);
				parent->set_left_child(new_node_2);
			}
		}
		else if(lr == 1)
		{
			if(randomizer == 0)
			{
				operands_to_used_(index_1, id);
				apoptosis_(parent->right_child(), id);
				parent->set_right_child(new_node_1);
			}
			else
			{
				operands_to_used_(index_2, id);
				apoptosis_(parent->right_child(), id);
				parent->set_right_child(new_node_2);
			}
		}
		else
		{
			std::cout << "Error l.549: maybe not corresponding parent-child nodes" << std::endl;
		}
	}

	//Not
	else
	{
		Node* new_node_not;

		int randomizer = rand() % 2;

		int lr = left_or_right_child_(position, parent);
		if(lr == 0)
		{
			if(randomizer == 0)
			{
				operands_to_used_(index_1, id);
				new_node_not = new Node(new_node_1, NULL, operator_not);
				apoptosis_(parent->left_child(), id);
				parent->set_left_child(new_node_not);
			}
			else
			{
				operands_to_used_(index_2, id);
				new_node_not = new Node(new_node_2, NULL, operator_not);
				apoptosis_(parent->left_child(), id);
				parent->set_left_child(new_node_not);
			}
		}
		else if(lr == 1)
		{
			if(randomizer == 0)
			{
				operands_to_used_(index_1, id);
				new_node_not = new Node(new_node_1, NULL, operator_not);
				apoptosis_(parent->right_child(), id);
				parent->set_right_child(new_node_not);
			}
			else
			{
				operands_to_used_(index_2, id);
				new_node_not = new Node(new_node_2, NULL, operator_not);
				apoptosis_(parent->right_child(), id);
				parent->set_right_child(new_node_not);
			}
		}
		else
		{
			std::cout << "Error l.597: maybe not corresponding parent-child nodes" << std::endl;
		}
	}
};

// auxiliary function to manage a replacement on an AND Node
void Evolution::replacement_and_management_(Node* position, Node* parent, Node* new_node_1, Node* new_node_2,
											int index_1, int index_2, int n, int id)
{
	//Racine ou noeud?
	if(parent == NULL)
	{
		//OR
		position -> set_value(operator_or);
	}
	else
	{
		//Differenciation de la modification
		//NOT
		if(n == 1)
		{
			Node* new_node_not;

			int randomizer = rand() % 2;

			int lr = left_or_right_child_(position, parent);
			if(lr == 0)
			{
				if(randomizer == 0)
				{
					new_node_not = new Node(new Node(*position->left_child()), NULL, operator_not);
					apoptosis_(parent->left_child(), id);
					re_operands_to_used_(new_node_not, id);
					parent->set_left_child(new_node_not);
				}
				else
				{
					new_node_not = new Node(new Node(*position->right_child()), NULL, operator_not);
					apoptosis_(parent->left_child(), id);
					re_operands_to_used_(new_node_not, id);
					parent->set_left_child(new_node_not);
				}
			}
			else if(lr == 1)
			{
				if(randomizer == 0)
				{
					new_node_not = new Node(new Node(*position->left_child()), NULL, operator_not);
					apoptosis_(parent->right_child(), id);
					re_operands_to_used_(new_node_not, id);
					parent->set_right_child(new_node_not);
				}
				else
				{
					new_node_not = new Node(new Node(*position->right_child()), NULL, operator_not);
					apoptosis_(parent->right_child(), id);
					re_operands_to_used_(new_node_not, id);
					parent->set_right_child(new_node_not);
				}
			}
			else
			{
				std::cout << "Error l.658: maybe not corresponding parent-child nodes" << std::endl;
			}
		}

		//Feuille - 1
		else if (n == 2)
		{
			int lr = left_or_right_child_(position, parent);
			if(lr == 0)
			{
				operands_to_used_(index_1, id);
				apoptosis_(parent->left_child(), id);
				parent->set_left_child(new_node_1);
			}
			else if(lr == 1)
			{
				operands_to_used_(index_1, id);
				apoptosis_(parent->right_child(), id);
				parent->set_right_child(new_node_1);
			}
			else
			{
				std::cout << "Error l.680: maybe not corresponding parent-child nodes" << std::endl;
			}
		}

		//Feuille - 0
		else if (n == 3)
		{
			int lr = left_or_right_child_(position, parent);
			if(lr == 0)
			{
				operands_to_used_(index_2, id);
				apoptosis_(parent->left_child(), id);
				parent->set_left_child(new_node_2);
			}
			else if(lr == 1)
			{
				operands_to_used_(index_2, id);
				apoptosis_(parent->right_child(), id);
				parent->set_right_child(new_node_2);
			}
			else
			{
				std::cout << "Error l.702: maybe not corresponding parent-child nodes" << std::endl;
			}
		}

		//OR
		else
		{
			position -> set_value(operator_or);
		}
	}
};

// auxiliary function to manage a replacement on an OR Node
void Evolution::replacement_or_management_(Node* position, Node* parent, Node* new_node_1, Node* new_node_2,
											int index_1, int index_2, int n, int id)
{
	//Racine ou noeud?
	if(parent == NULL)
	{
		//AND
		position -> set_value(operator_and);
	}
	else
	{
		//Differenciation de la modification
		//NOT
		if(n == 1)
		{
			Node* new_node_not;

			int randomizer = rand() % 2;

			int lr = left_or_right_child_(position, parent);
			if(lr == 0)
			{
				if(randomizer == 0)
				{
					new_node_not = new Node(new Node(*position->left_child()), NULL, operator_not);
					apoptosis_(parent->left_child(), id);
					re_operands_to_used_(new_node_not, id);
					parent->set_left_child(new_node_not);
				}
				else
				{
					new_node_not = new Node(new Node(*position->right_child()), NULL, operator_not);
					apoptosis_(parent->left_child(), id);
					re_operands_to_used_(new_node_not, id);
					parent->set_left_child(new_node_not);
				}
			}
			else if(lr == 1)
			{
				if(randomizer == 0)
				{
					new_node_not = new Node(new Node(*position->left_child()), NULL, operator_not);
					apoptosis_(parent->right_child(), id);
					re_operands_to_used_(new_node_not, id);
					parent->set_right_child(new_node_not);
				}
				else
				{
					new_node_not = new Node(new Node(*position->right_child()), NULL, operator_not);
					apoptosis_(parent->right_child(), id);
					re_operands_to_used_(new_node_not, id);
					parent->set_right_child(new_node_not);
				}
			}
			else
			{
				std::cout << "Error 770: maybe not corresponding parent-child nodes" << std::endl;
			}
		}

		//Feuille - 1
		else if (n == 2)
		{
			int lr = left_or_right_child_(position, parent);
			if(lr == 0)
			{
				operands_to_used_(index_1, id);
				apoptosis_(parent->left_child(), id);
				parent->set_left_child(new_node_1);
			}
			else if(lr == 1)
			{
				operands_to_used_(index_1, id);
				apoptosis_(parent->right_child(), id);
				parent->set_right_child(new_node_1);
			}
			else
			{
				std::cout << "Error l.792: maybe not corresponding parent-child nodes" << std::endl;
			}
		}

		//Feuille - 0
		else if (n == 3)
		{
			int lr = left_or_right_child_(position, parent);
			if(lr == 0)
			{
				operands_to_used_(index_2, id);
				apoptosis_(parent->left_child(), id);
				parent->set_left_child(new_node_2);
			}
			else if(lr == 1)
			{
				operands_to_used_(index_2, id);
				apoptosis_(parent->right_child(), id);
				parent->set_right_child(new_node_2);
			}
			else
			{
				std::cout << "Error l.814: maybe not corresponding parent-child nodes" << std::endl;
			}
		}

		//AND
		else
		{
			position -> set_value(operator_and);
		}
	}
};

// auxiliary function to manage a replacement on a NOT Node
void Evolution::replacement_not_management_(Node* position, Node* parent, Node* new_node_1, Node* new_node_2,
											int index_1, int index_2, int n, int id)
{
	//Racine ou noeud?
	if(parent == NULL)
	{
		//Differenciation de la modification
		//OR
		if(n == 1 || n == 3)
		{
			position -> set_value(operator_or);

			//Differenciaton de la valeur de la feuille droite ajoutée
			if(n == 1)
			{
				operands_to_used_(index_1, id);
				position -> set_right_child(new_node_1);
			}
			else
			{
				operands_to_used_(index_2, id);
				position -> set_right_child(new_node_2);
			}
		}

		//AND
		else if(n == 0 || n == 2)
		{
			position -> set_value(operator_and);

			//Differenciaton de la valeur de la feuille droite ajoutée
			if(n == 0)
			{
				operands_to_used_(index_1, id);
				position -> set_right_child(new_node_1);
			}
			else
			{
				operands_to_used_(index_2, id);
				position -> set_right_child(new_node_2);
			}
		}
	}
	else
	{
		//Differenciation de la modification
		//OR
		if(n == 1)
		{
			Node* new_node_or;

			int randomizer = rand() % 2;

			int lr = left_or_right_child_(position, parent);
			if(lr == 0)
			{
				if(randomizer == 0)
				{
					operands_to_used_(index_1, id);
					new_node_or = new Node(new Node(*position->left_child()), new_node_1, operator_or);
					apoptosis_(parent->left_child(), id);
					re_operands_to_used_(new_node_or, id);
					parent->set_left_child(new_node_or);
				}
				else
				{
					operands_to_used_(index_2, id);
					new_node_or = new Node(new Node(*position->left_child()), new_node_2, operator_or);
					apoptosis_(parent->left_child(), id);
					re_operands_to_used_(new_node_or, id);
					parent->set_left_child(new_node_or);
				}
			}
			else if(lr == 1)
			{
				if(randomizer == 0)
				{
					operands_to_used_(index_1, id);
					new_node_or = new Node(new Node(*position->left_child()), new_node_1, operator_or);
					apoptosis_(parent->right_child(), id);
					re_operands_to_used_(new_node_or, id);
					parent->set_right_child(new_node_or);
				}
				else
				{
					operands_to_used_(index_2, id);
					new_node_or = new Node(new Node(*position->left_child()), new_node_2, operator_or);
					apoptosis_(parent->right_child(), id);
					re_operands_to_used_(new_node_or, id);
					parent->set_right_child(new_node_or);
				}
			}
			else
			{
				std::cout << "Error l.920: maybe not corresponding parent-child nodes" << std::endl;
			}
		}

		//Feuille - 1
		else if (n == 2)
		{
			int lr = left_or_right_child_(position, parent);
			if(lr == 0)
			{
				operands_to_used_(index_1, id);
				apoptosis_(parent->left_child(), id);
				parent->set_left_child(new_node_1);
			}
			else if(lr == 1)
			{
				operands_to_used_(index_1, id);
				apoptosis_(parent->right_child(), id);
				parent->set_right_child(new_node_1);
			}
			else
			{
				std::cout << "Error l.942: maybe not corresponding parent-child nodes" << std::endl;
			}
		}

		//Feuille - 0
		else if (n == 3)
		{
			int lr = left_or_right_child_(position, parent);
			if(lr == 0)
			{
				operands_to_used_(index_2, id);
				apoptosis_(parent->left_child(), id);
				parent->set_left_child(new_node_2);
			}
			else if(lr == 1)
			{
				operands_to_used_(index_2, id);
				apoptosis_(parent->right_child(), id);
				parent->set_right_child(new_node_2);
			}
			else
			{
				std::cout << "Error l.964: maybe not corresponding parent-child nodes" << std::endl;
			}
		}

		//AND
		else
		{
			Node* new_node_and;

			int randomizer = rand() % 2;

			int lr = left_or_right_child_(position, parent);
			if(lr == 0)
			{
				if(randomizer == 0)
				{
					operands_to_used_(index_1, id);
					new_node_and = new Node(new Node(*position->left_child()), new_node_1, operator_and);
					apoptosis_(parent->left_child(), id);
					re_operands_to_used_(new_node_and, id);
					parent->set_left_child(new_node_and);
				}
				else
				{
					operands_to_used_(index_2, id);
					new_node_and = new Node(new Node(*position->left_child()), new_node_2, operator_and);
					apoptosis_(parent->left_child(), id);
					re_operands_to_used_(new_node_and, id);
					parent->set_left_child(new_node_and);
				}
			}
			else if(lr == 1)
			{
				if(randomizer == 0)
				{
					operands_to_used_(index_1, id);
					new_node_and = new Node(new Node(*position->left_child()), new_node_1, operator_and);
					apoptosis_(parent->right_child(), id);
					re_operands_to_used_(new_node_and, id);
					parent->set_right_child(new_node_and);
				}
				else
				{
					operands_to_used_(index_2, id);
					new_node_and = new Node(new Node(*position->left_child()), new_node_2, operator_and);
					apoptosis_(parent->right_child(), id);
					re_operands_to_used_(new_node_and, id);
					parent->set_right_child(new_node_and);
				}
			}
			else
			{
				std::cout << "Error l.1016: maybe not corresponding parent-child nodes" << std::endl;
			}
		}
	}
};

// generates and returns a vector containing the data of the csv file
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
// computes and returns the fitness for one Node
float Evolution::compute_fitness_(Node* node)
{
	int length = data_.size();
	float fit = 0;
	int i = 0;
	
	for (i = 0; i < length; ++i)
	{
		if(node->node_result(data_[i]) == data_[i][data_[i].size()-1]) // if the results of the formula is equal to the last column, adds 1 to the score of fitness
		{
			fit += 1;
		}
	}

	fit /= i; // average

	return fit;
};

// compares all mutants fitnesses and if one of them has a better fitness than the base Node, it becomes the new base Node for the following cycle
void Evolution::compare_fitness_()
{
	int index_of_best = 0;

	// Max fitness search
	for (int i = 0; i < fitnesses_.size()-1; ++i)
	{
		if(fitnesses_[i] < fitnesses_[i+1])
		{
			index_of_best = i+1;
		}
	}

	// if the max fitness found is higher than the base Node's fitness, the base Node becomes the Node which has the max fitness
	if(compute_fitness_(mutant_children_[index_of_best]) > compute_fitness_(root_))
	{
		root_ = mutant_children_[index_of_best];
	}
};