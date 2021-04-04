/****** BAEKJOON 14503 *****/
/***** SAMSUNG SW TEST *****/
/** Solved Date 2020-10-17 */

#include <iostream>
#include <vector>

using namespace std;

const int dx[4] = { -1, 0, 1, 0 };
const int dy[4] = { 0, 1, 0, -1 };

int main()
{
	int N, M;
	int x, y, d;
	cin >> N >> M >> x >> y >> d;


	vector<vector<int>> map(N, vector<int>(M, 1));
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			cin >> map[i][j];
		}
	}

	int can = 0;
	while (true)
	{
		// Clean
		if (map[x][y] == 0)
		{
			map[x][y] = 2;
			can++;
		}

		// Search
		int nx = x;
		int ny = y;
		int nd = d;
		for (int i = 0; i < 4; i++)
		{
			nd = (nd + 3) % 4;
			nx = x + dx[nd];
			ny = y + dy[nd];
			if (map[nx][ny] == 0)
				break;
		}

		// Go
		if (map[nx][ny] == 0)
		{
			x = nx;
			y = ny;
			d = nd;
			continue;
		}
		
		// Back
		nx = x - dx[d];
		ny = y - dy[d];
		if (map[nx][ny] == 2)
		{
			x = nx;
			y = ny;
			continue;
		}

		

		// Off
		break;
	}

	cout << can;
	
	return 0;
}