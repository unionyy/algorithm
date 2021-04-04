/****** BAEKJOON 3190 ******/
/***** SAMSUNG SW TEST *****/
/** Solved Date 2020-10-12 */

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int main()
{
	int N, K, L;
	vector<int> al1, al2;
	int dir = 0; // R D L U
	int head1, head2;
	queue<int> body1, body2, rt, rd;

	cin >> N >> K;

	vector<vector<int>> map(N, vector<int>(N, 0));
	for (int i = 0; i < K; i++)
	{
		int cl1, cl2;
		cin >> cl1 >> cl2;
		cl1--;
		cl2--;
		al1.push_back(cl1);
		al2.push_back(cl2);
		map[cl1][cl2] = 1;
	}

	cin >> L;

	for (int i = 0; i < L; i++)
	{
		int ct;
		char cd;
		cin >> ct >> cd;
		rt.push(ct);
		if (cd == 'D')
		{
			rd.push(1);
		}
		else
		{
			rd.push(3);
		}
	}

	// Make snake
	int time = 0;
	head1 = 0;
	head2 = 0;
	dir = 0;
	body1.push(head1);
	body2.push(head2);
	map[0][0] = 2;

	// Move
	while (true)
	{
		if (!rt.empty() && time == rt.front())
		{
			rt.pop();
			dir += rd.front();
			dir %= 4;
			rd.pop();
			
		}

		switch (dir)
		{
		case 0:
			head2++;
			break;
		case 1:
			head1++;
			break;
		case 2:
			head2--;
			break;
		case 3:
			head1--;
			break;
		}
		time++;
		// Game Over
		if (head1 < 0 || head1 >= N ||
			head2 < 0 || head2 >= N ||
			map[head1][head2] == 2)
			break;

		// Remove tale
		if (map[head1][head2] == 0)
		{
			int tmpl1 = body1.front();
			body1.pop();
			int tmpl2 = body2.front();
			body2.pop();
			map[tmpl1][tmpl2] = 0;
		}

		// Put head
		map[head1][head2] = 2;
		body1.push(head1);
		body2.push(head2);
	}

	cout << time;
	return 0;
}