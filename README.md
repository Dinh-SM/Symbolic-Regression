Symbolic-Regression
Goal : Find the best approximation
Content : 2 class --> Node : Treat the tree of the formula
		  --> Evolution : Modify the function
Node : 3 attributs (2 Node and 1 char*)

Constructor : Node(Node* lc, Node* rc, std::string v); plus destructor et getters
int node_result() : for have the result of the formula
Evolution : n attributs () - Use class Node

Node[ ] replication(Node parent_tree[], int number_of_child) : for create number_of_child children to the parent's formula
Node mutation(Node parent, Node parent_tree[]) : choose a mutation to a given node of the formula
Node insertion(Node parent, Node parent_tree[]) : make the mutation 'insertion' at a given place of the formula
Node deletion(Node parent, Node parent_tree[]) : make the mutation 'deletion' at a given place of the formula
Node replacement(Node parent) : make the mutation 'deletion' at a given node of the formula
int fitness(Node tree[ ]) : calculation of the fitness of a formula
Node * comparative_fitness (Node[] childre_tab, int number_of_child) : choose the best children of the formula
