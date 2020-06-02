#include"Evolution.cpp"

int main(int argc, char const *argv[])
{
	const std::string OPERAND_X42("42");
	const std::string OPERAND_X69("69");
	const std::string DATA("./binary_gene_expression_ACE2_tfs.csv");
	
	// base Node
	Node* g = new Node(NULL, NULL, OPERAND_X42); // Niveau 2
	Node* d = new Node(NULL, NULL, OPERAND_X69); // Niveau 2
	Node* racine = new Node(g, d, OPERATOR_AND); // Niveau 1

	Evolution e(racine, DATA);

	// cleans the file
	std::ofstream ofs;
	ofs.open("fitness_progression.out", std::ofstream::out | std::ofstream::trunc);
	ofs.close();

	// display base Node
	std::cout << "Formule arbre de base :" << std::endl;
	std::cout << racine->node_formula() << std::endl;
	std::cout << std::endl;
	std::vector<float> fitness_progression;

	// arguments management and algorithm execution
	// argv[1] is the number of cycles, argv[2] is the number of children and argv[3] is the csv file
	if(argc == 4)
	{
		std::stringstream argv_1;
		argv_1 << argv[1];
		int number_of_cycles;
		argv_1 >> number_of_cycles;

		std::stringstream argv_2;
		argv_2 << argv[2];
		int number_of_children;
		argv_2 >> number_of_children;

		e.set_data(std::string(argv[3]));
		
		if(number_of_cycles > 0 && number_of_children > 0)
		{
			fitness_progression = e.evolution(number_of_cycles, number_of_children);
		}
	}
	else
	{
		fitness_progression = e.evolution(150, 8); //10 cycles avec 5 enfants
	}

	// display of the best formula at the end
	std::cout << "Meilleure formule arbre après exécution :" << std::endl;
	std::cout << e.root()->node_formula() << std::endl;

	// serialization of fitness progression for plotting purpose
	for (int i = 0; i < fitness_progression.size(); ++i)
	{
		std::ofstream myfile;
		myfile.open("fitness_progression.out", std::ios_base::app);
		myfile << i << "\t" << fitness_progression[i] << std::endl;
		myfile.close();
	}

	return 0;
};