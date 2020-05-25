#include"Evolution.cpp"
#include<iostream>
#include<string>

int main(int argc, char const *argv[])
{
	std::string operand_true("1");
	std::string operand_false("0");
	std::string operator_or("OR");
	std::string operator_and("AND");
	std::string operator_not("NOT");
	
	Node gdg(NULL, NULL, operand_false); //Niveau4
	Node gauchedroite(&gdg, NULL, operator_not); // Niveau 3
	Node ggg(NULL, NULL, operand_true); //Niveau 4
	Node ggd(NULL, NULL, operand_true); //Niveau 4
	Node gauchegauche(&ggg, &ggd, operator_and); // Niveau 3
	Node gauche(&gauchegauche, &gauchedroite, operator_and); // Niveau 2

	Node dgg(NULL, NULL, operand_true); //Niveau 4
	Node dgd(NULL, NULL, operand_false); //Niveau 4
	Node droitegauche(&dgg, &dgd, operator_or); // Niveau 3
	Node droite(&droitegauche, NULL, operator_not); // Niveau 2

	Node racine(&gauche, &droite, operator_or); // Niveau 1

	std::cout << "Résultat arbre :" << std::endl;
	std::cout << racine.node_result() << std::endl;

	std::cout << "Résultat noeud gauche :" << std::endl;
	std::cout << gauche.node_result() << std::endl;

	std::cout << "Résultat noeud droite :" << std::endl;
	std::cout << droite.node_result() << std::endl;

	std::cout << "Formule arbre :" << std::endl;
	std::cout << racine.node_formula() << std::endl;


	Node copy(racine);
	Node dgd2(NULL, NULL, operand_true); //Niveau 4
	copy.right_child()->left_child()->set_right_child(&dgd2);

	std::cout << "Résultat arbre copié :" << std::endl;
	std::cout << copy.node_result() << std::endl;

	std::cout << "Résultat noeud gauche copié :" << std::endl;
	std::cout << copy.left_child()->node_result() << std::endl;

	std::cout << "Résultat noeud droite copié :" << std::endl;
	std::cout << copy.right_child()->node_result() << std::endl;

	std::cout << "Formule arbre copié :" << std::endl;
	std::cout << copy.node_formula() << std::endl;
	
	std::cout << "Formule arbre de base :" << std::endl;
	std::cout << racine.node_formula() << std::endl;


	/*Evolution evolution;
	for (int i = 0; i < 100; ++i)
	{
		evolution.mutation(racine, racine);
	}*/


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


	std::string operand_x1("x1");
	std::string operand_x2("x2");
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

	return 0;
}
