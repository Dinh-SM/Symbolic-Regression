#include"Node.cpp"
#include<iostream>
#include<string>

int main(int argc, char const *argv[])
{
	std::string operand_true("1");
	std::string operand_false("0");
	std::string operator_or("OR");
	std::string operator_and("AND");
	std::string operator_not("NOT");

	Node gaucgedroite(NULL, NULL, operand_true); // Niveau 3
	Node gauchegauche(NULL, NULL, operand_false); // Niveau 3
	Node gauche(&gauchegauche, &gaucgedroite, operator_and); // Niveau 2

	Node droitegauche(NULL, NULL, operand_false); // Niveau 3
	Node droite(&droitegauche, NULL, operator_not); // Niveau 2

	Node racine(&gauche, &droite, operator_or); // Niveau 1


	std::cout << "Résultat arbre :" << std::endl;
	std::cout << racine.node_result() << std::endl;

	std::cout << "Résultat noeud gauche :" << std::endl;
	std::cout << gauche.node_result() << std::endl;

	std::cout << "Résultat noeud droite :" << std::endl;
	std::cout << droite.node_result() << std::endl;


	return 0;
}