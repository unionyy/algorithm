/****** BAEKJOON 14502 *****/
/***** SAMSUNG SW TEST *****/
/** Solved Date 2020-10-14 */

#include <iostream>
#include <vector>

using namespace std;

const int dx[4] = { 0, 0, 1, -1 };
const int dy[4] = { 1, -1, 0, 0, };

void Spread(vector<vector<int>> &map, int N, int M)
{
	vector<vector<bool>> dp(N, vector<bool>(M, false));
	bool change = true;
	while (change)
	{
		change = false;

		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < M; j++)
			{
				if (map[i][j] == 2 && !dp[i][j])
				{
					dp[i][j] = true;
					for (int k = 0; k < 4; k++)
					{
						int nx = i + dx[k];
						int ny = j + dy[k];
						if (nx < 0 || nx >= N || ny < 0 || ny >= M)
							continue;

						if (map[nx][ny] == 0)
						{
							map[nx][ny] = 2;
							change = true;
						}
					}
				}
			}
		}
	}
	return;
}

int main()
{
	int N, M;

	cin >> N >> M;

	vector<vector<int>> map(N, vector<int>(M, 0));
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			cin >> map[i][j];
		}
	}

	int mmax = 0;
	int wall[3] = { 0, 1, 2 };
	while (true)
	{
		vector<vector<int>> cmap = map;
		bool wallwell = true;
		for (int i = 0; i < 3; i++)
		{
			if (cmap[wall[i] / M][wall[i] % M] == 0)
				cmap[wall[i] / M][wall[i] % M] = 1;
			else
			{
				wallwell = false;
				break;
			}
		}

		if (wallwell)
		{
			Spread(cmap, N, M);
			int safe = 0;
			for (int i = 0; i < N; i++)
			{
				for (int j = 0; j < M; j++)
				{
					if (cmap[i][j] == 0)
						safe++;
				}
			}
			mmax = max(safe, mmax);
		}

		if (wall[2] < N * M - 1)
			wall[2]++;
		else if (wall[1] < N * M - 2)
		{
			wall[1]++;
			wall[2] = wall[1] + 1;
		}	
		else if (wall[0] < N * M - 3)
		{
			wall[0]++;
			wall[1] = wall[0] + 1;
			wall[2] = wall[1] + 1;
		}
		else
			break;
	}

	cout << mmax;
	return 0;
}