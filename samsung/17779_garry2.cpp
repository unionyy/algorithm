/****** BAEKJOON 17779 *****/
/***** SAMSUNG SW TEST *****/
/** Solved Date 2020-10-14 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
	int N;
	cin >> N;

	vector<vector<int>> A(N, vector<int>(N, 0));
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cin >> A[i][j];
		}
	}

	int mmin = 40000;
	for (int x = 0; x < N; x++)
	{
		for (int y = 0; y < N; y++)
		{
			for (int d1 = 1; d1 < N; d1++)
			{
				for (int d2 = 1; d2 < N; d2++)
				{
					if (x + d1 + d2 >= N || y - d1 < 0 || y + d2 >= N)
						continue;
					vector<vector<int>> CA = A;
					vector<int> sum(5, 0);
					
					for (int j = 0; j <= min(d1, d2); j++)
					{
						int cx = x + j;
						int cd1 = d1 - j;
						int cd2 = d2 - j;
						for (int i = 0; i <= cd1; i++)
						{
							sum[4] += CA[cx + i][y - i];
							CA[cx + i][y - i] = 0;

							sum[4] += CA[cx + cd2 + i][y + cd2 - i];
							CA[cx + cd2 + i][y + cd2 - i] = 0;
						}
						for (int i = 0; i <= cd2; i++)
						{
							sum[4] += CA[cx + i][y + i];
							CA[cx + i][y + i] = 0;

							sum[4] += CA[cx + cd1 + i][y - cd1 + i];
							CA[cx + cd1 + i][y - cd1 + i] = 0;
						}
					}

					for (int i = 0; i < x + d1; i++)
					{
						for (int j = 0; j < y + 1; j++)
						{
							sum[0] += CA[i][j];
							CA[i][j] = 0;
						}
					}

					for (int i = 0; i < x + d2+1; i++)
					{
						for (int j = y + 1; j < N; j++)
						{
							sum[1] += CA[i][j];
							CA[i][j] = 0;
						}
					}

					for (int i = x + d1; i < N; i++)
					{
						for (int j = 0; j < y - d1 + d2; j++)
						{
							sum[2] += CA[i][j];
							CA[i][j] = 0;
						}
					}

					for (int i = x + d2 + 1; i < N; i++)
					{
						for (int j = y - d1 + d2; j < N; j++)
						{
							sum[3] += CA[i][j];
							CA[i][j] = 0;
						}
					}
					//cout << sum[0] << " " << sum[1] << " " << sum[2] << " " << sum[3] << " " << sum[4] << endl;
					sort(sum.begin(), sum.end());
					int tmp = sum[4] - sum[0];
					mmin = min(tmp, mmin);
				}
			}
		}
	}

	cout << mmin;

	return 0;
}