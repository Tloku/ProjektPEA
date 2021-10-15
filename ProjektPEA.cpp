#include <iostream>
#include "AdjacencyMatrix.h"
#include <fstream>
#include <string>

void loadFromFile();

AdjacencyMatrix mat = AdjacencyMatrix(4);

int main()
{
	mat.addEdge(0, 1, 10);
	mat.addEdge(0, 2, 15);
	mat.addEdge(0, 3, 20);
	mat.addEdge(1, 0, 10);
	mat.addEdge(1, 2, 35);
	mat.addEdge(1, 3, 25);
	mat.addEdge(2, 0, 15);
	mat.addEdge(2, 1, 35);
	mat.addEdge(2, 3, 30);
	mat.addEdge(3, 0, 20);
	mat.addEdge(3, 1, 25);
	mat.addEdge(3, 2, 30);

	mat.TSPbruteForce();
}

void loadFromFile()
{
	std::cin.clear();
	std::cin.ignore();

	std::fstream file;
	std::string fileName;
	int number_of_edges = 0;
	int number_of_nodes = 0;
	int begin, end, weight;

	std::cout << "\nWczytywanie z pliku.\n";
	std::cout << "\nPodaj nazwe pliku, z ktorego mam wczytac dane: ";

	getline(std::cin, fileName);

	file.open(fileName, std::ios::in);

	if (file.good() == false)
	{
		std::cout << "Nie udalo sie otworzyc pliku!\n";
	}
	else
	{
		std::cout << "Udalo sie otworzyc plik!\n";

		file >> number_of_edges;
		file >> number_of_nodes;
		mat = AdjacencyMatrix(number_of_nodes);

		for (int i = 0; i < number_of_edges; i++)
		{
			file >> begin; file >> end; file >> weight;
			mat.addEdge(begin, end, weight);
			mat.addEdge(end, begin, weight);
		}

	}
	file.close();
}