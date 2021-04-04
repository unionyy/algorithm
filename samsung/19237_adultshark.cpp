/****** BAEKJOON 19237 *****/
/***** SAMSUNG SW TEST *****/
/** Solved Date 2020-10-12 */

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const int DIR0[] = { -1, 1, 0, 0 };
const int DIR1[] = { 0, 0, -1, 1 };

int main()
{
	int N, M, K;
	cin >> N >> M >> K;

	vector<vector<int>> map(N, vector<int>(N, 0));
	vector<int> l0(M, -1);
	vector<int> l1(M, -1);
	vector<int> dir(M, -1);
	vector<vector<vector<int>>> pdir(M, vector<vector<int>>(4, vector<int>(4, -1)));

	// map, loc
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			int tmp;
			cin >> tmp;
			tmp--;
			map[i][j] = tmp;

			// shark
			if (tmp != -1)
			{
				l0[tmp] = i;
				l1[tmp] = j;
			}
		}
	}

	// first dir
	for (int i = 0; i < M; i++)
	{
		int tmp;
		cin >> tmp;
		tmp--;
		dir[i] = tmp;
	}

	// dir priority
	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			for (int k = 0; k < 4; k++)
			{
				int tmp;
				cin >> tmp;
				tmp--;
				pdir[i][j][k] = tmp;
			}
		}
	}

	// init smell
	vector<queue<int>> smell0(M, queue<int>());
	vector<queue<int>> smell1(M, queue<int>());
	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < K-1; j++)
		{
			smell0[i].push(-1);
			smell1[i].push(-1);
		}
		smell0[i].push(l0[i]);
		smell1[i].push(l1[i]);
	}

	// Play
	int snum = M;
	int time = 0;
	while (snum > 1 && time < 1000)
	{
		time++;

		// Move
		vector<vector<int>> tmap(N, vector<int>(N, -1));
		for (int i = 0; i < M; i++)
		{
			// X
			if (l0[i] == -1)
				continue;

			int nl0 = -1;
			int nl1 = -1;
			int ndir = -1;
			// Move to -1
			for (int j = 0; j < 4; j++)
			{
				int tdir = pdir[i][dir[i]][j];
				int tl0 = l0[i] + DIR0[tdir];
				int tl1 = l1[i] + DIR1[tdir];
				if (tl0 < 0 || tl0 >= N || tl1 < 0 || tl1 >= N)
					continue;
				if (map[tl0][tl1] < 0)
				{
					nl0 = tl0;
					nl1 = tl1;
					ndir = tdir;
					break;
				}
			}

			// Move to smell
			if (nl0 == -1)
			{
				for (int j = 0; j < 4; j++)
				{
					int tdir = pdir[i][dir[i]][j];
					int tl0 = l0[i] + DIR0[tdir];
					int tl1 = l1[i] + DIR1[tdir];
					if (tl0 < 0 || tl0 >= N || tl1 < 0 || tl1 >= N)
						continue;
					if (map[tl0][tl1] % M == i)
					{
						nl0 = tl0;
						nl1 = tl1;
						ndir = tdir;
						break;
					}
				}
			}
			// Move
			if (tmap[nl0][nl1] < 0)
			{
				tmap[nl0][nl1] = i;
				l0[i] = nl0;
				l1[i] = nl1;
				dir[i] = ndir;
			}
			// Get out
			else
			{
				l0[i] = -1;
				l1[i] = -1;
				dir[i] = -1;
				snum--;
			}
		}

		// Smelling
		for (int i = 0; i < M; i++)
		{
			// X
			if (l0[i] == -1)
				continue;

			smell0[i].push(l0[i]);
			smell1[i].push(l1[i]);

			if (map[l0[i]][l1[i]] < 0)
				map[l0[i]][l1[i]] = i;
			else
				map[l0[i]][l1[i]] += M;
		}

		// Unsmelling
		for (int i = 0; i < M; i++)
		{
			// X
			if (smell0[i].empty())
				continue;

			int ds0 = smell0[i].front();
			smell0[i].pop();
			int ds1 = smell1[i].front();
			smell1[i].pop();

			// X
			if (ds0 == -1)
				continue;

			map[ds0][ds1] -= M;
		}

	}

	if (snum > 1)
		cout << -1;
	else
		cout << time;

	return 0;
}