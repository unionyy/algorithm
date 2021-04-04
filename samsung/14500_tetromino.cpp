/****** BAEKJOON 14500 *****/
/***** SAMSUNG SW TEST *****/
/** Solved Date 2020-10-13 */

#include <iostream>
#include <vector>

using namespace std;

bool Check(int a, int b, int N, int M)
{
	if (a < 0 || a >= N || b < 0 || b >= M)
		return false;
	else
		return true;
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

	const int D00[19] = { 0, };
	const int D01[19] = { 0, };
	const int D10[19] = { 0, 1, 0, 1, 0, -1, 0, 1, 0, 0, 1, 0, -1, 0, 1, 1, 0, -1, 0 };
	const int D11[19] = { 1, 0, 1, 0, -1, 0, 1, 0, -1, 1, 0, -1, 0, 1, 0, 0, 1, 0, -1 };
	const int D20[19] = { 0, 2, 1, 2, 0, -2, 0, 1, 1, 1, 1, -1, -1, 1, 1, 2, 0, -2, 0 };
	const int D21[19] = { 2, 0, 0, 0, -2, 0, 2, 1, -1, 1, -1, -1, 1, 1, -1, 0, 2, 0, -2 };
	const int D30[19] = { 0, 3, 1, 2, 1, -2, -1, 2, 1, 0, 2, 0, -2, 1, 2, 2, 1, -2, -1 };
	const int D31[19] = { 3, 0, 1, 1, -2, -1, 2, 1, -2, 2, 0, -2, 0, 2, -1, -1, 2, 1, -2 };
	

	int max = 0;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			for (int k = 0; k < 19; k++)
			{
				if (!Check(i + D00[k], j + D01[k], N, M)) continue;
				if (!Check(i + D10[k], j + D11[k], N, M)) continue;
				if (!Check(i + D20[k], j + D21[k], N, M)) continue;
				if (!Check(i + D30[k], j + D31[k], N, M)) continue;
				int sum = 0;
				sum += map[i + D00[k]][j + D01[k]];
				sum += map[i + D10[k]][j + D11[k]];
				sum += map[i + D20[k]][j + D21[k]];
				sum += map[i + D30[k]][j + D31[k]];
				if (max < sum)
					max = sum;
			}

		}
	}
	cout << max;

	return 0;
}