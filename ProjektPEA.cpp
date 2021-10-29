#include <iostream>
#include "AdjacencyMatrix.h"
#include <fstream>
#include <string>

void loadFromFile();

AdjacencyMatrix mat = AdjacencyMatrix(5);

int main()
{
	loadFromFile();
	for (int i = 0; i < mat.x; i++)
		for (int j = 0; j < mat.x; j++)
			if (mat.V[i][j] == 0)
				mat.V[i][j] = INT_MAX;
	mat.displayMatrix();
	mat.minimalizeMatrix(mat.V);
	mat.displayMatrix();
	
}

void loadFromFile()
{
	std::fstream file;
	std::string fileName = "abdul.txt";
	int number_of_nodes = 0;
	int weight;

	std::cout << "Wczytywanie z pliku.\n";

	file.open(fileName, std::ios::in);
	
	if (file.good() == false) {
		std::cout << "Nie udalo sie otworzyc pliku!\n";
	}
	else {
		std::cout << "Udalo sie otworzyc plik!\n";

		file >> number_of_nodes;
		mat = AdjacencyMatrix(number_of_nodes);

		for (int i = 0; i < number_of_nodes; i++) {
			for (int j = 0; j < number_of_nodes; j++){
				file >> weight;
				mat.V[i][j] = weight;
			}
		}
	}
	file.close();
}