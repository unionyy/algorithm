/****** BAEKJOON 15684 *****/
/***** SAMSUNG SW TEST *****/
/** Solved Date 2020-10-16 */

#include <iostream>
#include <vector>

using namespace std;

bool Sim(int N, int H, vector<vector<bool>>& sun)
{
	vector<int> val;
	for (int i = 0; i < N; i++)
		val.push_back(i);

	for (int i = 0; i < H; i++)
	{
		for (int j = 0; j < N - 1; j++)
		{
			if (sun[i][j])
			{
				int tmp = val[j];
				val[j] = val[j + 1];
				val[j + 1] = tmp;
			}
		}
	}

	for (int i = 0; i < N; i++)
	{
		if (i != val[i])
			return false;
	}

	return true;
}

int main()
{
	int N, M, H;

	cin >> N >> M >> H;

	vector<vector<bool>> sun(H, vector<bool>(N - 1, false));
	
	for (int i = 0; i < M; i++)
	{
		int a, b;
		cin >> a >> b;
		sun[a - 1][b - 1] = true;
	}

	int as[] = { -1, -1, -1 };
	while (true)
	{
		// cal
		bool pos = true;
		for (int s : as)
		{
			if (s == -1)
				continue;

			int x = s / (N - 1);
			int y = s % (N - 1);

			if (sun[x][y] || (y > 0 && sun[x][y - 1]) || (y < N - 2 && sun[x][y + 1]))
			{
				for (int ss : as)
				{
					if (ss == s)
						break;
					else if (ss == -1)
						continue;
					int xx = ss / (N - 1); 
					int yy = ss % (N - 1);
					sun[xx][yy] = false;
				}

				pos = false;
				break;
			}
			else
				sun[x][y] = true;
		}
		// sim
		if (pos)
		{
			if (Sim(N, H, sun))
				break;

			for (int s : as)
			{
				if (s == -1)
					continue;
				int xx = s / (N - 1);
				int yy = s % (N - 1);
				sun[xx][yy] = false;
			}
		}

		
		

		as[2]++;
		if (as[2] != H * (N - 1))
			continue;
		as[1]++;
		as[2] = as[1] + 1;
		if (as[2] != H * (N - 1))
			continue;
		as[0]++;
		as[1] = as[0] + 1;
		as[2] = as[0] + 2;
		if (as[2] == H * (N - 1))
			break;

	}
	int ans;
	if (as[2] == H * (N - 1))
		ans = -1;
	else if (as[2] == -1)
		ans = 0;
	else if (as[1] == -1)
		ans = 1;
	else if (as[0] == -1)
		ans = 2;
	else
		ans = 3;
	cout << ans;

	return 0;
}