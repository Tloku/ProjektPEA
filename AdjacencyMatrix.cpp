#include "AdjacencyMatrix.h"

AdjacencyMatrix::AdjacencyMatrix() {}

AdjacencyMatrix::AdjacencyMatrix(int x)
{
	this->x = x;
	V = new int*[x];
	visited = new bool[x];
	reducedCost = 0;
	min_weight = INT_MAX;
	currentWeight = 0;
	currentBound = 0;

	for (int i = 0; i < x; i++)
		V[i] = new int[x];

	for (int i = 0; i < x; i++)
		for (int j = 0; j < x; j++)
			V[i][j] = 0;
}

void AdjacencyMatrix::addEdge(int i, int j, int weight)
{
	V[i][j] = weight;
}

void AdjacencyMatrix::displayMatrix()
{
	for (int i = 0; i < x; i++)
	{
		for (int j = 0; j < x; j++)
		{
			if (V[i][j] == INT_MAX)
				std::cout << "0 ";
			else
				std::cout << V[i][j] << " ";
		}
		std::cout << std::endl;
	}
}

void AdjacencyMatrix::TSPbruteForce()
{
	//Zmienna min_weight zostaje ustawiona na INT_MAX w konstruktorze
	int k = 0;
	long iterations = 0;
	int min_weight2; // zmienna min_weight2 jest zmienną pomocniczą do wypisywania drogi

	//Zostaje stworzony wektor przechowujący wszystkie wierzchołki 
	//z macierzy sąsiedztwa, oprócz wierzchołka startowego
	for (int i = 1; i < x; i++)
		vertex.push_back(i);
	
	timer = 0.0;

	counter.startCounter();
	do{
		iterations++;
		//Zmienna przechowująca wartości długości aktualnej drogi zostaje ustawiona na 0.
		//Zmienna k służąca do wskazywania wierzchołku startowego zostaje ustawiona na zerowy wierzchołek
		current_pathweight = 0;
		k = 0;
		for (int i = 0; i < vertex.size(); i++)
		{
			//Dodajemy do aktualnej drogi odległość od wierzchołka znajdującego się pod zmienną K do wierzchołka z wektora "vertex"
			current_pathweight += V[k][vertex[i]];
			//Wstawiamy do zmiennej K wartość wierzchołka z wektora "vertex"
			k = vertex[i];
			
		}
		//Droga kończy się w wierzchołku startowym, więc do aktualnej drogi musimy dodać
		//odległość od ostatniego wierzchołka w wektorze "vertex" do wierzchołka początkowego
		current_pathweight += V[k][0];

		min_weight2 = min_weight; 

		//Sprawdzamy, która wartość jest większa: aktualnej drogi, czy minimalnej drogi
		//Wybieramy tą mniejszą i przypisujemy ją do wartości min_weight
		min_weight = min(current_pathweight, min_weight);

		if (min_weight2 > current_pathweight)
		{
			path.clear();
			path.push_back(0);
			for (int i = 0; i < x - 1; i++)
				path.push_back(vertex[i]);
		}
	} while (std::next_permutation(vertex.begin(), vertex.end()));

	timer = counter.getCounter();

	
	std::cout << "Time: " << std::setprecision(8) << timer << " (ms)" << std::endl;
	std::cout << "Solution: " << min_weight << std::endl;
	std::cout << "Iterations: " << iterations << std::endl;
	std::cout << "Path: ";
	for (int i : path)
		std::cout << i << " - ";
	std::cout << "0";
	getchar();
}

int AdjacencyMatrix::minimalizeMatrix(int **V)
{
	int* minRow = new int[x];
	int* minCol = new int[x];

	for (int i = 0; i < x; i++)
		minRow[i] = minCol[i] = INT_MAX;

	for (int i = 0; i < x; i++)
		for (int j = 0; j < x; j++)
			if (V[i][j] < minRow[i])
				minRow[i] = V[i][j];

	for (int i = 0; i < x; i++)
		for (int j = 0; j < x; j++)
		{
			if (V[i][j] != INT_MAX && minRow[i] != INT_MAX)
				V[i][j] -= minRow[i];
			if (V[i][j] < minCol[j])
				minCol[j] = V[i][j];
		}				

	for (int i = 0; i < x; i++)
		for (int j = 0; j < x; j++)
			if (V[i][j] != INT_MAX && minCol[j] != INT_MAX)
				V[i][j] -= minCol[j];

	for (int i = 0; i < x; i++)
		reducedCost += minRow[i] + minCol[i];

	return reducedCost;
}

int AdjacencyMatrix::findMin(int i)
{
	int min = INT_MAX;
	int j;
	for (j = 0; j < x; j++)
		if (V[i][j] < min && i != j)
			min = V[i][j];
	return j;
}

//void AdjacencyMatrix::rowReduction(int row[], int x)
//{
//	memset(row, INT_MAX, x);
//	
//	for (int i = 0; i < x; i++)
//		for (int j = 0; j < x; j++)
//			if (V[i][j] < row[i])
//				row[i] = V[i][j];
//	
//	for (int i = 0; i < x; i++)
//		for (int j = 0; j < x; j++)
//			if (V[i][j] != INT_MAX && row[i] != INT_MAX)
//				V[i][j] -= row[i];
//	
//}
//
//void AdjacencyMatrix::columnReduction(int col[], int x)
//{
//	memset(col, INT_MAX, x);
//
//	for (int i = 0; i < x; i++)
//		for (int j = 0; j < x; j++)
//			if (V[i][j] < col[j])
//				col[j] = V[i][j];
//
//	for (int i = 0; i < x; i++)
//		for (int j = 0; j < x; j++)
//			if (V[i][j] != INT_MAX && col[j] != INT_MAX)
//				V[i][j] -= col[j];
//
//}
//
//int AdjacencyMatrix::calculateCost()
//{
//	
//	int cost = 0;
//	int *row, *col;
//	row = new int[x];
//	col = new int[x];
//
//	rowReduction(row, x);
//	columnReduction(col, x);
//
//
//	for (int i = 0; i < x; i++)
//	{
//		cost += (row[i] != INT_MAX) ? row[i] : 0;
//		cost += (col[i] != INT_MAX) ? col[i] : 0;
//	}
//
//
//	return cost;
//}


void AdjacencyMatrix::BranchAndBound()
{
	/*memset(visited, 0, x);
	visited[0] = true;
	currentPath.push_back(0);

	BranchAndBoundRec(1);*/

	memset(visited, 0, x);
	std::vector<int> searchTree;

	minimalizeMatrix(V);
	searchTree.push_back(0);

	while (!searchTree.empty())
	{
		int nextCity = findMin(0);

	}

}