//#include"Node.cpp"
#include<iostream>
#include<string>
#include"Evolution.cpp"

int main(int argc, char const *argv[])
{
	const std::string operand_true("1");
	const std::string operand_false("0");
	const std::string operator_or("OR");
	const std::string operator_and("AND");
	const std::string operator_not("NOT");
	const std::string operand_x1("x1");
	const std::string operand_x2("x2");
	
	Node* gdg = new Node(NULL, NULL, operand_x2); //Niveau4
	Node* gd = new Node(gdg, NULL, operator_not); // Niveau 3
	Node* ggg = new Node(NULL, NULL, operand_x1); //Niveau 4
	Node* ggd = new Node(NULL, NULL, operand_x1); //Niveau 4
	Node* gg = new Node(ggg, ggd, operator_and); // Niveau 3
	Node* g = new Node(gg, gd, operator_and); // Niveau 2

	Node* dgg = new Node(NULL, NULL, operand_x1); //Niveau 4
	Node* dgd = new Node(NULL, NULL, operand_x2); //Niveau 4
	Node* dg = new Node(dgg, dgd, operator_or); // Niveau 3
	Node* d = new Node(dg, NULL, operator_not); // Niveau 2

	Node* racine = new Node(g, d, operator_and); // Niveau 1

	Evolution e(racine);

	/*
	//Test delete_blood()
		std::cout<<"formule originale :" <<droite.node_formula()<<'\n';
		droite.delete_blood();
		std::cout <<"nouvelle formule : " << droite.node_formula() << '\n';
	*/	
	
	/*
	// parcours à partir d'un string
	// si le chemin mène à rien à un moment, il donne le dernier noeud sur le chemin
	std::string path("gdg");
	Node* current_node = &racine;
	for (int i = 0; i < path.length(); ++i)
	{
		if(path.c_str()[i] == 'g' && current_node->left_child() != NULL)
		{
			current_node = current_node->left_child();
		}
		else if(path.c_str()[i] == 'd' && current_node->right_child() != NULL)
		{
			current_node = current_node->right_child();
		}
		else
		{
			break;
		}
	}
	std::cout << current_node->value() << std::endl;

	Node gdg3(NULL, NULL, operand_x1); //Niveau4
	Node gd3(&gdg3, NULL, operator_not); // Niveau 3
	Node ggg3(NULL, NULL, operand_x2); //Niveau 4
	Node ggd3(NULL, NULL, operand_x2); //Niveau 4
	Node gg3(&ggg3, &ggd3, operator_and); // Niveau 3
	Node g3(&gg3, &gd3, operator_and); // Niveau 2

	Node dgg3(NULL, NULL, operand_x2); //Niveau 4
	Node dgd3(NULL, NULL, operand_x1); //Niveau 4
	Node dg3(&dgg3, &dgd3, operator_or); // Niveau 3
	Node d3(&dg3, NULL, operator_not); // Niveau 2

	Node racine3(&g3, &d3, operator_or); // Niveau 1

	std::cout << "Résultat arbre avec x1 et x2 :" << std::endl;
	std::cout << racine3.node_result(1, 0) << std::endl;
	std::cout << "Formule arbre avec x1 et x2 :" << std::endl;
	std::cout << racine3.node_formula() << std::endl;
	
	std::cout << "Résultat arbre de base :" << std::endl;
	std::cout << racine.node_result() << std::endl;
	std::cout << "Formule arbre de base :" << std::endl;
	std::cout << racine.node_formula() << std::endl;
*/

/*//Test replacement
	
	Node rep_node(racine);	
	
	std::cout << "Replacement!!" << std::endl;

//	rep_node.set_value(operator_and);

	std::cout << "Résultat arbre :" << std::endl;
	std::cout << rep_node.node_result() << std::endl;

	std::cout << "Formule arbre :" << std::endl;
	std::cout << rep_node.node_formula() << std::endl;

	std::cout << "Modification..." << std::endl;

	e.Evolution::replacement(&rep_node, rep_node);
	
	std::cout << "Formule arbre :" << std::endl;
	std::cout << rep_node.node_formula() << std::endl;


	std::cout << "Résultat arbre :" << std::endl;
	std::cout << rep_node.node_result() << std::endl;

	std::cout << "Modification le retour..." << std::endl;

	e.Evolution::replacement(&rep_node, rep_node);
	
	std::cout << "Formule arbre :" << std::endl;
	std::cout << rep_node.node_formula() << std::endl;

	std::cout << "Résultat arbre :" << std::endl;
	std::cout << rep_node.node_result() << std::endl;

	std::cout << "Modifiectaion du premier enfants!" << std::endl;

	std::cout << "Résultat noeud gauche :" << std::endl;
	std::cout << gauche.node_formula() << std::endl;

	std::cout << "Formule arbre :" << std::endl;
	std::cout << racine.node_formula() << std::endl;

	std::cout << "Eh oh Eh oh" << std::endl;

	e.Evolution::replacement(&gauche, rep_node);

	std::cout << "Résultat noeud gauche :" << std::endl;
	std::cout << gauche.node_formula() << std::endl;
	
	std::cout << "Formule arbre :" << std::endl;
	std::cout << racine.node_formula() << std::endl;*/

	/*std::cout << "EXECUTE ORDER 66" << std::endl;
	std::vector<Node*> children(5);
	children = e.replication_(5);
	for (int i = 0; i < 5; ++i)
	{
		std::cout << "Formule arbre #" << i << " :" << std::endl;
		std::cout << children[i]->node_formula() << std::endl;
	}*/

	std::cout << "Formule arbre de base :" << std::endl;
	std::cout << racine->node_formula() << std::endl;
	std::vector<Node*> children;
	children = e.evolution(1, 18);

	for (int i = 0; i < 18; ++i)
	{
		std::cout << "Formule arbre mutant #" << i << " :" << std::endl;
		std::cout << children[i]->node_formula() << std::endl;
		std::cout << children[i]->node_result(1, 0) << std::endl;
	}

	return 0;

}


