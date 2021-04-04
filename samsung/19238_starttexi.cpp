/****** BAEKJOON 19238 *****/
/***** SAMSUNG SW TEST *****/
/** Solved Date 2020-10-14 */

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const int dx[] = { -1, 1, 0, 0 };
const int dy[] = { 0, 0, -1, 1 };

int Search(int N, vector<vector<int>>& map, int& x, int& y, int target)
{
	queue<int> xq;
	queue<int> yq;
	queue<int> fq;
	vector<vector<bool>> visit(N, vector<bool>(N, false));

	xq.push(x);
	yq.push(y);
	fq.push(0);
	
	int fuel = -1;
	while (!xq.empty())
	{
		int cx = xq.front(); xq.pop();
		int cy = yq.front(); yq.pop();
		int cf = fq.front(); fq.pop();

		if (fuel != -1 && fuel < cf)
			continue;

		if (cx < 0 || cx >= N || cy < 0 || cy >= N)
			continue;

		if (map[cx][cy] == -1)
			continue;



		if (visit[cx][cy])
			continue;

		visit[cx][cy] = true;

		if (map[cx][cy] != 0 && (target == -1 || map[cx][cy] == target))
		{
			if (fuel == -1 || cx < x || (cx == x && cy < y))
			{
				x = cx;
				y = cy;
				fuel = cf;
				if (target != -1)
					break;
			}
		}
		else
		{
			for (int i = 0; i < 4; i++)
			{
				xq.push(cx + dx[i]);
				yq.push(cy + dy[i]);
				fq.push(cf + 1);
			}
		}
	}
	return fuel;
}

int main()
{
	int N, M, fuel;

	cin >> N >> M >> fuel;

	vector<vector<int>> pmap(N, vector<int>(N, 0));
	vector<vector<int>> dmap(N, vector<int>(N, 0));
	int x, y;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			int tmp;
			cin >> tmp;
			if (tmp == 1)
			{
				pmap[i][j] = -1;
				dmap[i][j] = -1;
			}
		}
	}
	cin >> x >> y;
	x--;
	y--;

	vector<int> destx;
	vector<int> desty;
	for (int i = 0; i < M; i++)
	{
		int px, py, dx, dy;
		cin >> px >> py >> dx >> dy;
		pmap[px-1][py-1] = i + 1;
		dmap[dx-1][dy-1] = i + 1;
		destx.push_back(dx - 1);
		desty.push_back(dy - 1);
	}

	for (int i = 0; i < M; i++)
	{
		int cf = Search(N, pmap, x, y, -1);
		if (cf == -1 || cf > fuel)
		{
			fuel = -1;
			break;
		}
		fuel -= cf;
		int target = pmap[x][y];
		pmap[x][y] = 0;

		dmap[destx[target - 1]][desty[target - 1]] = target;
		cf = Search(N, dmap, x, y, target);
		if (cf == -1 || cf > fuel)
		{
			fuel = -1;
			break;
		}
		fuel += cf;
		dmap[x][y] = 0;
	}
	cout << fuel;

	return 0;
}
