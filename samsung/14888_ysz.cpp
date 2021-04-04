/****** BAEKJOON 14888 *****/
/***** SAMSUNG SW TEST *****/
/** Solved Date 2020-10-17 */

#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

vector<int> vals;

void Cal(vector<int>& nums, int N, vector<int> ys, int o, int val)
{

	if (o == N)
	{
		vals.push_back(val);
		return;
	}

	if (ys[0] > 0)
	{
		int nval = val + nums[o];
		vector<int> nys = ys;
		nys[0]--;
		Cal(nums, N, nys, o + 1, nval);
	}
	if (ys[1] > 0)
	{
		int nval = val - nums[o];
		vector<int> nys = ys;
		nys[1]--;
		Cal(nums, N, nys, o + 1, nval);
	}
	if (ys[2] > 0)
	{
		int nval = val * nums[o];
		vector<int> nys = ys;
		nys[2]--;
		Cal(nums, N, nys, o + 1, nval);
	}
	if (ys[3] > 0)
	{
		int nval = val / nums[o];
		vector<int> nys = ys;
		nys[3]--;
		Cal(nums, N, nys, o + 1, nval);
	}

}

int main()
{
	int N;
	cin >> N;
	vector<int> nums(N, 0);
	for (int i = 0; i < N; i++)
		cin >> nums[i];

	vector<int> ys(4, 0);
	for (int i = 0; i < 4; i++)
		cin >> ys[i];
	Cal(nums, N, ys, 1, nums[0]);

	sort(vals.begin(), vals.end());

	cout << vals.back() << endl;
	cout << vals[0] << endl;

	return 0;
}