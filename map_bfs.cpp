#include <iostream>
#include <vector>
#include <utility>
#include <queue>

using namespace std;
using vi=vector<int>;
using ull=unsigned long long;

bool vs[1005][1005];

bool safe(int i, int j, int n, int m)
{
	if (i < 0 || i >= n) return false;
	if (j < 0 || j >= m) return false;

	return true;
}

int solve(const vector<vector<int>> &tab, pair<int, int> & start, pair<int, int> & end, int n, int m)
{
	queue<pair<pair<int, int>, int>> q;

	q.push({{start.first, start.second}, 1});
	vs[start.first][start.second] = 1;

	while (not q.empty())
	{
		pair<int, int> u = q.front().first;
		int nops = q.front().second;
		q.pop();

		if (u == end)
			return nops;


		vector<pair<int, int>> adj;

		if (safe(u.first, u.second + 1, n, m) && tab[u.first][u.second + 1] > 0)
			adj.push_back({u.first, u.second + 1});
		if (safe(u.first, u.second - 1, n, m) && tab[u.first][u.second - 1] > 0)
			adj.push_back({u.first, u.second - 1});
		if (safe(u.first + 1, u.second, n, m) && tab[u.first + 1][u.second] > 0)
			adj.push_back({u.first + 1, u.second});
		if (safe(u.first - 1, u.second, n, m) && tab[u.first - 1][u.second] > 0)
			adj.push_back({u.first - 1, u.second});

		for (auto p : adj)
		{
			if (!vs[p.first][p.second])
			{
				vs[p.first][p.second] = 1;
				q.push({p, nops+1});
			}
		}
	}

	return -1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

	int n, m; 
	cin >> n >> m;
	pair<int, int> start, end;
	vector<vector<int>> tab(n, vector<int>(m));

	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
		{
			cin >> tab[i][j];

			if (tab[i][j] == 2)
				start = make_pair(i, j);
			
			if (tab[i][j] == 3)
				end = make_pair(i, j);
		}

	int ans = solve(tab, start, end, n, m);

	cout << ans << "\n";
	
    
    return 0;
}

