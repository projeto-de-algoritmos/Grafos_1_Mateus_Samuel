#include <iostream>
#include <vector>
#include <utility>
#include <queue>
#include <cstdio>
#include <string>

#define X_MAX 1005
#define Y_MAX 1005

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

int solve(
		const std::vector<std::string> &tab,
		const std::pair<int, int> & start, 
		const std::pair<int, int> & end, 
		int n, int m)
{
	/*  pair of a coordinate and the number of moves until that point
	 *  example: {{1, 2}, 4} means that 4 steps were necessary to reach the
	 *  coordinate [1,2]
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

		if (is_valid(v.first, v.second + 1, n, m) and tab[v.first][v.second + 1] != '#') //checks if moving UP is valid
			adj.push_back({v.first, v.second + 1});

		if (is_valid(v.first, v.second - 1, n, m) and tab[v.first][v.second - 1] != '#') //checks if moving DOWN is valid
			adj.push_back({v.first, v.second - 1});

		if (is_valid(v.first + 1, v.second, n, m) and tab[v.first + 1][v.second] != '#') //checks if moving RIGHT is valid
			adj.push_back({v.first + 1, v.second});

		if (is_valid(v.first - 1, v.second, n, m) and tab[v.first - 1][v.second] != '#') //checks if moving LEFT is valid
			adj.push_back({v.first - 1, v.second});

		for (auto p : adj)
		{
			if (not visited[p.first][p.second])
			{
				visited[p.first][p.second] = 1;
				q.push({p, no_of_steps+1});
			}
		}
	}

	return -1;
}

int main() {
	std::freopen("map.txt", "r", stdin);

	int n, m; 
	std::cin >> n >> m;

	std::pair<int, int> start, end;
	std::vector<std::string> tab(n, std::string(m, '#'));
	
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
		{
			std::cin >> tab[i][j];

			if (tab[i][j] == 'S')
				start = std::make_pair(i, j);
			
			if (tab[i][j] == 'E')
				end = std::make_pair(i, j);
		}

	int no_of_steps = solve(tab, start, end, n, m);

	if (no_of_steps != -1)
		std::cout << "Menor quantidade de movimentos necessarios para chegar ao fim: " << no_of_steps << "\n";
	else
		std::cout << "Nao ha caminho valido\n";
    
    return 0;
}

