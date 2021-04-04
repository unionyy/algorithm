/****** BAEKJOON 14499 *****/
/***** SAMSUNG SW TEST *****/
/** Solved Date 2020-10-13 */

#include <iostream>
#include <vector>

using namespace std;

const int D0[] = { 0, 0, -1, 1 };
const int D1[] = { 1, -1, 0, 0 };

int main()
{
	int N, M, x, y, K;
	cin >> N >> M >> x >> y >> K;

	vector<vector<int>> map(N, vector<int>(M, 0));
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			cin >> map[i][j];
		}
	}

	vector<int> order(K, 0);
	for (int i = 0; i < K; i++)
	{
		int tmp;
		cin >> tmp;
		order[i] = tmp - 1;
	}

	int dice[6] = { 0, };
	int over = 0;
	int east = 2;
	int north = 1;
	for (int cor : order)
	{
		int nx = x + D0[cor];
		int ny = y + D1[cor];
		if (nx < 0 || nx >= N || ny < 0 || ny >= M)
			continue;
		x = nx;
		y = ny;

		int odir[] = { 5 - east, east, 5 - north, north };
		int edir[] = { over, 5 - over, east, east };
		int ndir[] = { north, north, over, 5 - over };
		over = odir[cor];
		east = edir[cor];
		north = ndir[cor];

		if (map[x][y] == 0)
		{
			map[x][y] = dice[5 - over];
		}
		else
		{
			dice[5 - over] = map[x][y];
			map[x][y] = 0;
		}
		cout << dice[over] << endl;
	}


	return 0;
}