/****** BAEKJOON 15686 *****/
/***** SAMSUNG SW TEST *****/
/** Solved Date 2021-04-18 */

#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>

using namespace std;

int main() {
    int N, M;
    cin >> N >> M;

    int map[50][50];
    int hnum = 0;
    int cnum = 0;
    vector<vector<int>> home;
    vector<vector<int>> ckn;

    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            cin >> map[i][j];
            if(map[i][j] == 1) {
                hnum++;
                home.push_back({i, j});
            } else if(map[i][j] == 2) {
                cnum++;
                ckn.push_back({i, j});
            }
        }
    }

    int dis[100][13];

    for(int i = 0; i < hnum; i++) {
        for(int j = 0; j < cnum; j++) {
            dis[i][j] = abs(home[i][0] - ckn[j][0]) + abs(home[i][1] - ckn[j][1]);
        }
    }

    int com[13] = {0, };

    for(int i = 0; i < M; i++) {
        com[i] = 1;
    }

    int minC = 10000;

    do {
        int cknL = 0;
        for(int i = 0; i < hnum; i++) {
            int min = 100;
            for(int j = 0; j < cnum; j++) {
                if(com[j] == 0) continue;

                if(min > dis[i][j]) min = dis[i][j];
            }
            cknL += min;
        }

        if(minC > cknL) minC = cknL;
    } while(prev_permutation(com, com + cnum));

    cout << minC;
}