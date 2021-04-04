/****** BAEKJOON 19235 *****/
/***** SAMSUNG SW TEST *****/
/** Solved Date 2020-10-13 */

#include <iostream>
#include <vector>

using namespace std;

void Down(vector<vector<int>> &gm, int t, int x, int y);

void Check(vector<vector<int>> &gm, int x, int y)
{
	if (x < 0)
		return;
	switch (gm[x][y])
	{
	case 0:
		break;
	case 1:
	case 2:
	case 3:
		Down(gm, gm[x][y], x, y);
		break;
	case 4:
		Down(gm, 2, x, y - 1);
		break;
	}
	return;
}

void Down(vector<vector<int>> &gm, int t, int x, int y)
{
	int bin = x;
	for (int j = x+1; j < 6; j++)
	{
		if (gm[j][y] != 0)
			break;
		else
			bin = j;
	}
	if (x == bin)
		return;
	if (t == 1)
	{
		gm[x][y] = 0;
		gm[bin][y] = 1;
		Check(gm, x - 1, y);
	}
	else if (t == 3)
	{
		if (x != 0)
		{
			gm[x][y] = 0;
			gm[x - 1][y] = 0;
		}
		gm[bin][y] = 3;
		gm[bin - 1][y] = 6;
		if (bin - 2 >= 0)
			Check(gm, x - 2, y);
	}
	else
	{
		int bin2 = x;
		for (int j = x+1; j < 6; j++)
		{
			if (gm[j][y + 1] != 0)
				break;
			else
				bin2 = j;
		}
		if (bin2 == x)
			return;
		bin = min(bin, bin2);

		gm[x][y] = 0;
		gm[x][y+1] = 0;
		gm[bin][y] = 2;
		gm[bin][y + 1] = 4;
		Check(gm, x - 1, y);
		Check(gm, x - 1, y + 1);
	}
}

int Remove(vector<vector<int>> &gm)
{
	vector<int> rmxs;
	for (int i = 2; i < 6; i++)
	{
		int cnt = 0;
		for (int j = 0; j < 4; j++)
		{
			if (gm[i][j] == 0)
				break;
			else
				cnt++;
		}
		if (cnt == 4)
			rmxs.push_back(i);
	}

	// Remove
	for (int rmx : rmxs)
	{
		for (int j = 0; j < 4; j++)
		{
			if (gm[rmx][j] == 3)
				gm[rmx - 1][j] = 1;
			else if (gm[rmx][j] == 6)
				gm[rmx + 1][j] = 1;
			gm[rmx][j] = 0;
		}
	}

	// Check
	for (int rmx : rmxs)
	{
		for (int j = 0; j < 4; j++)
		{
			Check(gm, rmx - 1, j);
		}
	}

	if (rmxs.size() != 0)
		return rmxs.size() + Remove(gm);
	else
		return 0;
}

int main()
{
	int N;
	cin >> N;
	vector<int> ts(N, -1);
	vector<int> xs(N, -1);
	vector<int> ys(N, -1);

	for (int i = 0; i < N; i++)
	{
		int t, x, y;
		cin >> t >> x >> y;
		ts[i] = t;
		xs[i] = x;
		ys[i] = y;
	}

	// Green
	int score = 0;
	vector<vector<int>> gm(6, vector<int>(4, 0)); // mono 1, garo 2, sero 3
	vector<vector<int>> gmb(6, vector<int>(4, 0));
	for (int i = 0; i < N; i++)
	{
		// push block
		Down(gm, ts[i], 0, ys[i]);
		score += Remove(gm);

		// push block blue
		int tsb = ts[i];
		if (tsb == 2)
			tsb = 3;
		else if (tsb == 3)
			tsb = 2;
		Down(gmb, tsb, 0, xs[i]);
		score += Remove(gmb);

		// x = 0, 1
		int rmx = 0;
		int rmxb = 0;
		for (int i = 0; i <= 1; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				if (gm[i][j] != 0)
				{
					rmx++;
					break;
				}
			}
		}
		for (int i = 0; i <= 1; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				if (gmb[i][j] != 0)
				{
					rmxb++;
					break;
				}
			}
		}
		for (int i = 6 - rmx; i < 6; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				if (gm[i][j] == 0)
					gm[i][j] = 1;
			}
		}
		for (int i = 6 - rmxb; i < 6; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				if (gmb[i][j] == 0)
					gmb[i][j] = 1;
			}
		}
		Remove(gm);
		Remove(gmb);
	}
	int cnt1 = 0;
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (gm[i][j] != 0)
				cnt1++;
			if (gmb[i][j] != 0)
				cnt1++;
		}
	}
	cout << score << endl;
	cout << cnt1;

	return 0;
}