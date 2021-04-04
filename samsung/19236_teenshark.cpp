/****** BAEKJOON 19236 *****/
/***** SAMSUNG SW TEST *****/
/** Solved Date 2020-10-12 */

#include <iostream>
#include <vector>
#include <stack>

using namespace std;

int main()
{
	vector<int> dir(16, -1);
	vector<int> l1(16, -1);
	vector<int> l2(16, -1);
	vector<vector<int>> map(4, vector<int>(4, -1));

	int score = 0;
	int sl1, sl2, sdir;


	// get data
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			int ddir, nnum;
			cin >> nnum >> ddir;
			nnum--;
			dir[nnum] = ddir;
			l1[nnum] = i;
			l2[nnum] = j;
			map[i][j] = nnum;
		}
	}



	// put shark
	int cnum = map[0][0];
	score = cnum+1;
	sdir = dir[cnum];
	sl1 = 0;
	sl2 = 0;

	l1[cnum] = -1;
	l2[cnum] = -1;
	dir[cnum] = -1;
	map[0][0] = 100;


	stack<int> scs;
	stack<vector<int>> l1s;
	stack<vector<int>> l2s;
	stack<vector<int>> dirs;
	stack<vector<vector<int>>> maps;
	stack<int> sl1s;
	stack<int> sl2s;
	stack<int> sdirs;

	scs.push(score);
	l1s.push(l1);
	l2s.push(l2);
	dirs.push(dir);
	maps.push(map);
	sl1s.push(sl1);
	sl2s.push(sl2);
	sdirs.push(sdir);

	int max = 0;
	while (!scs.empty())
	{
		score = scs.top(); scs.pop();
		l1 = l1s.top(); l1s.pop();
		l2 = l2s.top(); l2s.pop();
		dir = dirs.top(); dirs.pop();
		map = maps.top(); maps.pop();
		sl1 = sl1s.top(); sl1s.pop();
		sl2 = sl2s.top(); sl2s.pop();
		sdir = sdirs.top(); sdirs.pop();

		if (max < score)
		{
			max = score;
		}

		// Move
		for (int i = 0; i < 16; i++)
		{
			if (l1[i] == -1)
				continue;

			int nl1 = -1;
			int nl2 = -1;
			for (int j = 0; j < 8; j++)
			{
				int cnl1 = -1;
				int cnl2 = -1;
				switch ((j + dir[i]) % 8)
				{
				case 1:
					cnl1 = l1[i] - 1;
					cnl2 = l2[i];
					break;
				case 2:
					cnl1 = l1[i] - 1;
					cnl2 = l2[i] - 1;
					break;
				case 3:
					cnl1 = l1[i];
					cnl2 = l2[i] - 1;
					break;
				case 4:
					cnl1 = l1[i] + 1;
					cnl2 = l2[i] - 1;
					break;
				case 5:
					cnl1 = l1[i] + 1;
					cnl2 = l2[i];
					break;
				case 6:
					cnl1 = l1[i] + 1;
					cnl2 = l2[i] + 1;
					break;
				case 7:
					cnl1 = l1[i];
					cnl2 = l2[i] + 1;
					break;
				case 0:
					cnl1 = l1[i] - 1;
					cnl2 = l2[i] + 1;
					break;
				}
				if (cnl1 < 0 || cnl1 >= 4 || cnl2 < 0 || cnl2 >= 4)
					continue;
				else if (map[cnl1][cnl2] == 100)
					continue;
				else
				{
					nl1 = cnl1;
					nl2 = cnl2;
					dir[i] = (j + dir[i]) % 8;
					break;
				}
			}
			if (nl1 == -1) continue;
			int tmp = map[nl1][nl2];
			map[nl1][nl2] = i;
			if (tmp != -1)
			{
				l1[tmp] = l1[i];
				l2[tmp] = l2[i];
			}

			map[l1[i]][l2[i]] = tmp;
			l1[i] = nl1;
			l2[i] = nl2;
			
			
		}

		

		// Eat
		for (int i = 0; i < 3; i++)
		{
			int cnl1 = -1;
			int cnl2 = -1;
			switch (sdir % 8)
			{
			case 1:
				cnl1 = sl1 - 1 - i;
				cnl2 = sl2;
				break;
			case 2:
				cnl1 = sl1 - 1 - i;
				cnl2 = sl2 - 1 - i;
				break;
			case 3:
				cnl1 = sl1;
				cnl2 = sl2 - 1 - i;
				break;
			case 4:
				cnl1 = sl1 + 1 + i;
				cnl2 = sl2 - 1 - i;
				break;
			case 5:
				cnl1 = sl1 + 1 + i;
				cnl2 = sl2;
				break;
			case 6:
				cnl1 = sl1 + 1 + i;
				cnl2 = sl2 + 1 + i;
				break;
			case 7:
				cnl1 = sl1;
				cnl2 = sl2 + 1 + i;
				break;
			case 0:
				cnl1 = sl1 - 1 - i;
				cnl2 = sl2 + 1 + i;
				break;
			}
			if (cnl1 < 0 || cnl1 >= 4 || cnl2 < 0 || cnl2 >= 4)
				continue;
			else if (map[cnl1][cnl2] == -1)
				continue;
			else
			{
				vector<int> tl1 = l1;
				vector<int> tl2 = l2;
				vector<int> tdir = dir;
				vector<vector<int>> tmap = map;
				int nsdir = dir[map[cnl1][cnl2]];
				tl1[map[cnl1][cnl2]] = -1;
				tl2[map[cnl1][cnl2]] = -1;
				tdir[map[cnl1][cnl2]] = -1;
				tmap[cnl1][cnl2] = 100;
				tmap[sl1][sl2] = -1;

				scs.push(score + map[cnl1][cnl2]+1);
				l1s.push(tl1);
				l2s.push(tl2);
				dirs.push(tdir);
				maps.push(tmap);
				sl1s.push(cnl1);
				sl2s.push(cnl2);
				sdirs.push(nsdir);

			}
		}
	}

	cout << max;
}