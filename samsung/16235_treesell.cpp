/****** BAEKJOON 16235 *****/
/***** SAMSUNG SW TEST *****/
/** Solved Date 2020-10-16 */

#include <iostream>
#include <vector>
#include <queue>
#include <functional>

using namespace std;

const int dx[8] = { -1, -1, -1, 0, 0, 1, 1, 1 };
const int dy[8] = { -1, 0, 1, -1, 1, -1, 0, 1 };
int main()
{
	int N, M, K;
	cin >> N >> M >> K;

	vector<vector<int>> A(N, vector<int>(N, 0));
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cin >> A[i][j];
		}
	}
	priority_queue<int, vector<int>, greater<int>> a;
	vector<vector<int>> nut(N, vector<int>(N, 5));
	vector<vector<int>> dt(N, vector<int>(N, 0));
	vector<vector<vector<int>>> tree(N, vector<vector<int>>(N, vector<int>()));

	for (int i = 0; i < M; i++)
	{
		int cx, cy, ca;
		cin >> cx >> cy >> ca;
		tree[--cx][--cy].push_back(ca);
	}

	for (int year = 0; year < K; year++)
	{
		// Spring
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				vector<int> ct = tree[i][j];
				vector<int> nt;
				for(int cct : ct)
				{
					if (cct > nut[i][j])
					{
						dt[i][j] += cct/2;
					}
					else
					{
						nut[i][j] -= cct;
						nt.push_back(cct + 1);
					}
				}
				tree[i][j] = nt;
			}
		}

		// Summer
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				nut[i][j] += dt[i][j];
				dt[i][j] = 0;
			}
		}

		// Fall
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				vector<int> ct = tree[i][j];
				for(int cct : ct)
				{
					if (cct % 5 == 0)
					{
						for (int k = 0; k < 8; k++)
						{
							if (i + dx[k] < 0 || i + dx[k] >= N)
								continue;
							else if (j + dy[k] < 0 || j + dy[k] >= N)
								continue;
							tree[i + dx[k]][j + dy[k]].insert(tree[i + dx[k]][j + dy[k]].begin(), 1);
						}
					}
				}
			}
		}

		// Winter
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				nut[i][j] += A[i][j];
			}
		}
	}

	int tnum = 0;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			tnum += tree[i][j].size();
		}
	}
	cout << tnum;

	return 0;
}