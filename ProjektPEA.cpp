#include <iostream>
#include "AdjacencyMatrix.h"
#include <fstream>
#include <string>
#include "PerformanceCounter.h"
#include <sstream>

void loadFromFile(std::string fileName);
void loadINIFile();
void saveToCsv(std::string txtFileName, int iterations, int optimalSolution, std::vector<int> optimalPath, double* timer, int* solution);

PerformanceCounter *counter;
AdjacencyMatrix mat = AdjacencyMatrix(5);
double* timer;
int* solution;

int main()
{
	loadINIFile();
}

void loadFromFile(std::string fileName)
{
	std::fstream file;
	int number_of_nodes = 0;
	int weight;

	file.open(fileName, std::ios::in);

	if (file.good() == false) {
		std::cout << "Nie udalo sie otworzyc pliku!\n";
	}
	else {
		//std::cout << "Udalo sie otworzyc plik!\n";

		file >> number_of_nodes;
		mat = AdjacencyMatrix(number_of_nodes);

		for (int i = 0; i < number_of_nodes; i++) {
			for (int j = 0; j < number_of_nodes; j++) {
				file >> weight;
				mat.V[i][j] = weight;
			}
		}
	}
	file.close();
}

void loadINIFile()
{
	std::fstream file;
	std::string fileName = "Badania.INI";
	int number_of_nodes = 0;
	int weight;

	std::string txtFileName;
	int iterations;
	int optimalSolution;
	std::vector<int> optimalPath;
	char tmpVector = ' ';

	file.open(fileName, std::ios::in);

	if (file.good())
	{
		std::string line;
		while (getline(file, line))
		{
			std::istringstream iss(line);

			iss >> txtFileName;
			iss >> iterations;
			iss >> optimalSolution;
			while (iss >> tmpVector){
				if (tmpVector == '[' || tmpVector == ']')
					continue;

				optimalPath.push_back(tmpVector);
			}
			timer = new double[iterations];
			counter = new PerformanceCounter[iterations];
			solution = new int[iterations];

			for (int k = 0; k < iterations; k++){
				timer[k] = 0;
				solution[k] = 0;
			}
				
			
			for (int i = 0; i < iterations; i++){
				loadFromFile(txtFileName);
				std::cout << "Plik: " << txtFileName << "\n";
				std::cout << "Optymalny wynik: " << optimalSolution << "\n";
				std::cout << "Optymalna sciezka: ";
				for (auto a : optimalPath)
					std::cout << a - '0' << " - ";
				std::cout << "\n";

				for (int k = 0; k < mat.x; k++)
					for (int j = 0; j < mat.x; j++)
						if (k == j)
							mat.V[k][j] = INT_MAX;
				
				counter[i].startCounter();
				solution[i] = mat.startHeldKarp();
				timer[i] = counter[i].getCounter();
				std::cout << "Wynik: " << solution[i] << "\n";
				std::cout << "Czas wykonania: " << timer[i] << "\n";
				std::cout << "\n\n";

				for (int i = 0; i < mat.x; i++) 
					delete[] mat.V[i];	
				delete[] mat.V;
			}
			saveToCsv(txtFileName, iterations, optimalSolution, optimalPath, timer, solution);
			optimalPath.clear();
		}
		delete[]solution;
		delete[]timer;
		delete[]counter;
	}
}

void saveToCsv(std::string txtFileName, int iterations, int optimalSolution, std::vector<int> optimalPath, double* timer, int* solution)
{
	std::fstream file;
	std::string fileName = "test_out_.csv";
	
	file.open(fileName, std::ios::out | std::ios::app);

	if (file.good()){
		file << txtFileName<<";";
		file << iterations << ";";
		file << optimalSolution << ";";
		file << "[";
		for (auto a : optimalPath)
			file << a - '0' << " ";
		file << "]" << ";\n";

		for (int i = 0; i < iterations; i++)
			file << std::to_string(timer[i]) << ";"<<solution[i]<<";\n";
		
	}


}