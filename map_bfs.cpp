#include <iostream>
#include <vector>
#include <utility>
#include <queue>
#include <cstdio>

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
		const std::vector<std::vector<int>> &tab,
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
		std::pair<int, int> u = q.front().first;
		int nops = q.front().second;
		q.pop();

		if (u == end)
			return nops;


		std::vector<std::pair<int, int>> adj;

		if (is_valid(u.first, u.second + 1, n, m) and tab[u.first][u.second + 1] > 0)
			adj.push_back({u.first, u.second + 1});

		if (is_valid(u.first, u.second - 1, n, m) and tab[u.first][u.second - 1] > 0)
			adj.push_back({u.first, u.second - 1});

		if (is_valid(u.first + 1, u.second, n, m) and tab[u.first + 1][u.second] > 0)
			adj.push_back({u.first + 1, u.second});

		if (is_valid(u.first - 1, u.second, n, m) and tab[u.first - 1][u.second] > 0)
			adj.push_back({u.first - 1, u.second});

		for (auto p : adj)
		{
			if (not visited[p.first][p.second])
			{
				visited[p.first][p.second] = 1;
				q.push({p, nops+1});
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
	std::vector<std::vector<int>> tab(n, std::vector<int>(m));
	
	//TODO: Use char instead of int
	
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
		{
			std::cin >> tab[i][j];

			if (tab[i][j] == 2)
				start = std::make_pair(i, j);
			
			if (tab[i][j] == 3)
				end = std::make_pair(i, j);
		}

	int no_of_steps = solve(tab, start, end, n, m);

	if (no_of_steps != -1)
		std::cout << "Menor quantidade de movimentos necessarios para chegar ao fim: " << no_of_steps << "\n";
	else
		std::cout << "Nao ha caminho valido\n";
    
    return 0;
}

