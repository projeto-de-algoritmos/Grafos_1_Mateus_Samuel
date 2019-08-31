#include <iostream>
#include <vector>
#include <utility>
#include <queue>
#include <cstdio>
#include <string>
#include <map>

#define X_MAX 1005
#define Y_MAX 1005

#define WALL_CHAR '#'
#define PATH_CHAR '.'
#define SPATH_CHAR '-'

bool visited[X_MAX][Y_MAX];

/*
 * Returns true if a given coordinate is valid (it doesn't exceed the matrix
 * size)
 */
bool is_valid(int i, int j, int n, int m)
{
	if (i < 0 or i >= n) return false;
	if (j < 0 or j >= m) return false;

	return true;
}

int bfs(
		const std::vector<std::string> &matrix,
		const std::pair<int, int> & start, 
		const std::pair<int, int> & end, 
		std::map<std::pair<int, int>, std::pair<int, int>> & previous,
		int n, int m)
{
	/*  pair of a coordinate and the number of moves until that point
	 *  example: {{1, 2}, 4} means that 4 steps were necessary to reach the
	 *  coordinate [1,2] from a given starting point
	 */
	std::queue<std::pair<std::pair<int, int>, int>> q; 

	q.push({{start.first, start.second}, 0});
	visited[start.first][start.second] = true;

	while (not q.empty())
	{
		std::pair<int, int> v = q.front().first;
		int no_of_steps = q.front().second;
		q.pop();

		if (v == end) // if the current node in the queue is the end, return the number of moves
			return no_of_steps;


		std::vector<std::pair<int, int>> adj; //adjacent cells of the current node in the queue

		if (is_valid(v.first, v.second + 1, n, m) and matrix[v.first][v.second + 1] != WALL_CHAR) //checks if moving UP is valid
			adj.push_back({v.first, v.second + 1});

		if (is_valid(v.first, v.second - 1, n, m) and matrix[v.first][v.second - 1] != WALL_CHAR) //checks if moving DOWN is valid
			adj.push_back({v.first, v.second - 1});

		if (is_valid(v.first + 1, v.second, n, m) and matrix[v.first + 1][v.second] != WALL_CHAR) //checks if moving RIGHT is valid
			adj.push_back({v.first + 1, v.second});

		if (is_valid(v.first - 1, v.second, n, m) and matrix[v.first - 1][v.second] != WALL_CHAR) //checks if moving LEFT is valid
			adj.push_back({v.first - 1, v.second});

		for (auto p : adj)
		{
			if (not visited[p.first][p.second])
			{
				visited[p.first][p.second] = true;
				previous[p] = v;
				q.push({p, no_of_steps+1});
			}
		}
	}

	return -1;
}

void add_shortest_path_to_matrix(
		std::vector<std::string> &matrix,
		std::map<std::pair<int, int>, std::pair<int, int>> previous,
		const std::pair<int, int> & start,
		const std::pair<int, int> & end)
{
	std::pair<int, int> aux = previous[end];

	while (aux != start)
	{
		matrix[aux.first][aux.second] = SPATH_CHAR;
		aux = previous[aux];
	}

}


void print_matrix(const std::vector<std::string> &matrix)
{
	for (auto line : matrix)
		std::cout << line << "\n";

	std::cout << "\n";
}

int main() {
	std::freopen("map.txt", "r", stdin);

	int n, m; 
	std::cin >> n >> m; //matrix dimensions

	std::pair<int, int> start, end; // pair of coordinates of the starting point and ending point
	std::vector<std::string> matrix(n, std::string(m, '#')); // our map
	std::map<std::pair<int, int>, std::pair<int, int>> previous; // dict to track a node's parent
	
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
		{
			std::cin >> matrix[i][j];

			if (matrix[i][j] == 'S')
				start = std::make_pair(i, j);
			
			if (matrix[i][j] == 'E')
				end = std::make_pair(i, j);
		}

	int no_of_steps = bfs(matrix, start, end, previous, n, m);

	if (no_of_steps != -1)
	{
		std::cout << "Menor quantidade de movimentos necessarios para chegar ao fim: " << no_of_steps << "\n";
		
		add_shortest_path_to_matrix(matrix, previous, start, end);

		std::cout << "Caminho necessario, marcado com \'" << SPATH_CHAR << "\':\n";
		print_matrix(matrix);
	}
	else
		std::cout << "Nao ha caminho valido\n";
    
    return 0;
}

