#include "AdjacencyMatrix.h"
#include <queue>
#include "Comparator.h"

AdjacencyMatrix::AdjacencyMatrix() {
}

AdjacencyMatrix::AdjacencyMatrix(int x)
{
	this->x = x;
	V = new int* [x];
	visited = new bool[x];
	
	min_weight = INT_MAX;
	currentWeight = 0;
	currentBound = 0;
	minRow = new int[x];
	minCol = new int[x];

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

int** AdjacencyMatrix::initNodeMatrix(int** nodeReducedMatrix)
{
	nodeReducedMatrix = new int* [x];
	for (int i = 0; i < x; i++)
		nodeReducedMatrix[i] = new int[x];

	return nodeReducedMatrix;
}

AdjacencyMatrix* AdjacencyMatrix::newNode(int **parentMatrix, std::vector<int> const& path, int level, int i, int j)
{
	AdjacencyMatrix* node = new AdjacencyMatrix;
	node->nodeReducedMatrix = initNodeMatrix(node->nodeReducedMatrix);
	node->nodePath = path;

	for (int i = 0; i < x; i++)
		for (int j = 0; j < x; j++)
			node->nodeReducedMatrix[i][j] = parentMatrix[i][j];			//przypisz nowemu węzłu wartości macierzy rodzica


	for (int k = 0; k < x && level != 0; k++){
		node->nodeReducedMatrix[i][k] = INT_MAX;		//ustaw wartości kolumny i wierszy macierzy na INT_MAX
		node->nodeReducedMatrix[k][j] = INT_MAX;
	}

	node->nodeReducedMatrix[j][0] = INT_MAX;			//ustaw wartość drogi od tego węzła do wezła początkowego na 0
	node->nodeLevel = level;
	node->nodeVertex = j;

	return node;
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
	do {
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

int AdjacencyMatrix::minimalizeMatrix(int** V)
{
	reducedCost = 0;

	for (int i = 0; i < x; i++)
		minRow[i] = minCol[i] = INT_MAX;

	for (int i = 0; i < x; i++)
		for (int j = 0; j < x; j++)
			if (V[i][j] < minRow[i])
				minRow[i] = V[i][j];

	for (int i = 0; i < x; i++)
		for (int j = 0; j < x; j++)
			if (V[i][j] != INT_MAX && minRow[i] != INT_MAX)
				V[i][j] -= minRow[i];
			

	for (int i = 0; i < x; i++)
		for (int j = 0; j < x; j++)
			if (V[i][j] < minCol[j])
				minCol[j] = V[i][j];


	for (int i = 0; i < x; i++)
		for (int j = 0; j < x; j++)
			if (V[i][j] != INT_MAX && minCol[j] != INT_MAX)
				V[i][j] -= minCol[j];

	for (int i = 0; i < x; i++) {
		if (minRow[i] != INT_MAX)
			reducedCost += minRow[i];
		if (minCol[i] != INT_MAX)
			reducedCost += minCol[i];
	}
		
	return reducedCost;
}

void AdjacencyMatrix::printPath(std::vector<int> const& path)
{
	for (int i = 0; i < path.size(); i++) {
		std::cout << path[i]+1 << "-";
	}
	std::cout << "\n";
}

int AdjacencyMatrix::branchAndBound()
{
	int previousVertex;
	std::priority_queue<AdjacencyMatrix*, std::vector<AdjacencyMatrix*>, Comparator> searchTree;
	std::vector<int> path;		//inicjalizacja zmiennych i kolejki piorytetowej

	AdjacencyMatrix *root = newNode(V, path, 0, -1, 0);			//stworzenie korzenia drzewa przeszukiwan
	root->nodeCost = minimalizeMatrix(root->nodeReducedMatrix); //minimalizacja macierzy korzenia

	searchTree.push(root);				//Dodanie korzenia do drzewa przeszukiwan
	path.clear();
	previousVertex = root->nodeVertex;
	

	while (!searchTree.empty())	//dopóki kolejka nie jest pusta
	{
		AdjacencyMatrix* minimumCostNode = searchTree.top();	//stwórz węzeł o wartościach węzła o najkrótszej ścieżce znajdującego się w kolejce
		
		searchTree.pop();	//usun szczyt kolejki
		int i = minimumCostNode->nodeVertex;
		
		if (previousVertex != i)
			minimumCostNode->nodePath.push_back(previousVertex);

		if (minimumCostNode->nodeLevel == x-1){		// jesli doszlismy juz do ostatniego poziomu, to zwróć wynik
			printPath(minimumCostNode->nodePath);
			return minimumCostNode->nodeCost;
		}

		for (int j = 0; j < x; j++){
			if (minimumCostNode->nodeReducedMatrix[i][j] != INT_MAX){
				AdjacencyMatrix* child = newNode(minimumCostNode->nodeReducedMatrix,		//stworz wezel - dziecko, z takimi parametrami jak te węzła minCostNode
					minimumCostNode->nodePath, minimumCostNode->nodeLevel + 1, i, j);		//zwiększ level o jeden

																							//koszt przejsca = koszt węzła minCostNode + wartość tablicy MinCostNode[i][j]
																							//+ koszt zminimalizowanej macierzy dziecka
				child->nodeCost = minimumCostNode->nodeCost + minimumCostNode->nodeReducedMatrix[i][j] +
					minimalizeMatrix(child->nodeReducedMatrix);
				
				searchTree.push(child);														//dodaj dziecko do kolejki
			}
		}
		if (nodeLevel > 0)
			previousVertex = minimumCostNode->nodeVertex;
		delete minimumCostNode;
	}
}

int AdjacencyMatrix::heldKarp(int** V, int pos, int visited, std::vector<std::vector<int>>& state)
{
	if (visited == ((1 << x) - 1)) //jeśli odwiedziliśmy wszystkie miasta, powróć do miasta początkowego
		return V[pos][0];		

	if (state[pos][visited] != INT_MAX)
		return state[pos][visited];		//jeśli posiadamy już wartość tego podzbioru, to zwracamy ją

	for (int i = 0; i < x; i++){
		if (i == pos || (visited & (1 << i)))
			continue; //jeśli i wskazuje na miejsce, w którym już byliśmy to pomijamy te iteracje pętli

		int distance = V[pos][i] + heldKarp(V, i, visited | (1 << i), state); //rekruencyjnie wywołujemy funckje heldKarp
		if (distance < state[pos][visited])									  //w visited ustawiamy bit odpowiadający miastu, w którym teraz jesteśmy na 1
			state[pos][visited] = distance;		//jeśli dystans do danego podzbioru okazał się mniejszy niż wartość w tablicy, to podmieniamy te wartość
	}
	return state[pos][visited];
}

int AdjacencyMatrix::startHeldKarp()
{
	std::vector<std::vector<int>> state(x);

	for (auto& neighbors : state)
		neighbors = std::vector<int>((1 << x) - 1, INT_MAX); // tworzymy tablicę 2D i inicjalizujemy ją INT_MAX

	int minimum = heldKarp(V, 0, 1, state);

	return minimum;
}