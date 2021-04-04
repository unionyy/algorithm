/****** BAEKJOON 16236 *****/
/***** SAMSUNG SW TEST *****/
/** Solved Date 2020-10-12 */

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

bool CMP(vector<int> a, vector<int> b)
{
	if (a[0] != b[0])
		return a[0] < b[0];
	else
		return a[1] < b[1];
}


bool Scan(int l1, int l2, int size, int n, int t, vector<vector<int>> &map, queue<vector<int>> &mq, vector<vector<bool>> &check)
{
	if (n <= l1 || n <= l2 || l1 < 0 || l2 < 0)
		return false;
	if (check[l1][l2])
		return false;
	check[l1][l2] = true;

	int tgt = map[l1][l2];
	
	if (tgt == size || tgt == 0)
	{
		vector<int> tmp;
		tmp.push_back(l1);
		tmp.push_back(l2);
		tmp.push_back(t);
		mq.push(tmp);
		return false;
	}
	else if (tgt < size)
		return true;
	else
		return false;
	
}

int main()
{
	int n;
	int l1, l2;
	int size = 2;
	int stm = 0;
	int time = 0;
	queue<vector<int>> mq;

	cin >> n;

	vector<vector<int>> map(n, vector<int>(n, 0));
	

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			int fish;
			cin >> fish;

			if (fish == 9)
			{
				l1 = i;
				l2 = j;
			}
			else if (fish != 0)
			{
				map[i][j] = fish;
			}
		}
	}

	while (true)
	{
		vector<vector<bool>> check(n, vector<bool>(n, false));
		check[l1][l2] = true;
		vector<int> tmp;
		tmp.push_back(l1);
		tmp.push_back(l2);
		tmp.push_back(0);
		mq.push(tmp);

		int dst = -1;
		vector<vector<int>> tgts;
		while (!mq.empty())
		{
			vector<int> ttmp = mq.front();
			mq.pop();
			int cl1, cl2, ct;
			cl1 = ttmp[0];
			cl2 = ttmp[1];
			ct = ttmp[2];

			if (dst == ct)
				continue;


			if (Scan(cl1 - 1, cl2, size, n, ct + 1, map, mq, check))
			{
				dst = ct + 1;
				ttmp[0] -= 1;
				ttmp[2]++;
				tgts.push_back(ttmp);
				continue;
			}
			if (Scan(cl1, cl2 - 1, size, n, ct + 1, map, mq, check))
			{
				dst = ct + 1;
				ttmp[1] -= 1;
				ttmp[2]++;
				tgts.push_back(ttmp);
				continue;
			}
			
			if (Scan(cl1, cl2 + 1, size, n, ct + 1, map, mq, check))
			{
				dst = ct + 1;
				ttmp[1] += 1;
				ttmp[2]++;
				tgts.push_back(ttmp);
				continue;
			}
			if (Scan(cl1 + 1, cl2, size, n, ct + 1, map, mq, check))
			{
				dst = ct + 1;
				ttmp[0] += 1;
				ttmp[2]++;
				tgts.push_back(ttmp);
				continue;
			}

		}

		if (tgts.empty())
			break;

		sort(tgts.begin(), tgts.end(), CMP);

		l1 = tgts[0][0];
		l2 = tgts[0][1];
		time += tgts[0][2];
		stm++;
		if (stm == size)
		{
			stm = 0;
			size++;
		}
		map[l1][l2] = 0;
	}

	cout << time;

}