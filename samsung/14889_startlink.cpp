/****** BAEKJOON 14889 *****/
/***** SAMSUNG SW TEST *****/
/** Solved Date 2021-04-14 */

#include <iostream>
#include <vector>

using namespace std;


int main()
{
	int N;

	cin >> N;

    vector<vector<int>> S(N, vector<int>(N, 0));

    for (int i = 0; i < N; i ++) {
        for (int j = 0; j < N; j++) {
            int s;
            cin >> s;
            S[i][j] = s;
        }
    }
	
	vector<bool> isA(N, false);

    for(int i = 0; i < N / 2; i++) {
        isA[i] = true;
    }

    int min = 1000000;
    while(true) {
        int sumA = 0;
        int sumB = 0;

        for(int i = 0; i < N; i++) {
            for(int j = 0; j < N; j++) {
                if(isA[i] && isA[j]) {
                    sumA += S[i][j];
                } else if(!isA[i] && !isA[j]) {
                    sumB += S[i][j];
                }
            }
        }
        int del = sumA - sumB;
        if(del == 0) {
            min = 0;
            break;
        } else if(del < 0) {
            del = 0 - del;
        }

        if(del < min) {
            min = del;
        }

        // Combination
        int cnt = 1;
        bool cngd = false;
        for(int i = N - 1; i > 0; i--) {
            if(!isA[i] && isA[i - 1]) {
                for(int j = 0; j < cnt; j++) {
                    isA[i + j] = true;
                    isA[i - 1] = false;
                }
                cngd = true;
                break;
            } else if(isA[i]) {
                cnt++;
                isA[i] = false;
            }
        }
        if(!cngd) {
            break;
        }
    }
    cout << min;
}