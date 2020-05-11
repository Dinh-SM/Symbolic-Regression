#include"Node.cpp"
#include<iostream>
#include<string>

int main(int argc, char const *argv[])
{
	std::string t("1");
	std::string f("0");
	std::string o("OR");
	std::string a("AND");
	std::string n("NOT");
	Node gauche(NULL, NULL, t);
	Node droite(NULL, NULL, f);
	Node racine(&gauche, &droite, o);

	std::cout << racine.node_result() << std::endl;

	return 0;
}