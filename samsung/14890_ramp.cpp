/****** BAEKJOON 14890 *****/
/***** SAMSUNG SW TEST *****/
/** Solved Date 2021-04-15 */

#include <iostream>

using namespace std;

int N, L;

int find(int map[][100]) {
    int cnt = 0;
     for(int i = 0; i < N; i++) {
        bool pos = true;
        int ramp[100] = {0, };
        for(int j = 1; j < N; j++) {
            if(map[i][j-1] == map[i][j]) {
                continue;
            } else if(abs(map[i][j-1] - map[i][j]) > 1) {
                pos = false;
                break;
            } else if(map[i][j-1] > map[i][j]) {
                for(int k = 0; k < L; k++) {
                    if(j + k > N - 1) {
                        pos = false;
                        break;
                    } else if(map[i][j] != map[i][j + k]) {
                        pos = false;
                        break;
                    } else {
                        ramp[j + k]++;
                    }
                }
            } else if(map[i][j-1] < map[i][j]) {
                for(int k = 0; k < L; k++) {
                    if(j - 1 - k < 0) {
                        pos = false;
                        break;
                    } else if(map[i][j - 1] != map[i][j - 1 - k]) {
                        pos = false;
                        break;
                    } else {
                        ramp[j - 1 - k]++;
                    }
                }
            }
        }
        for (int k = 0; k < N; k++) {
            if (ramp[k] > 1) {
                pos = false;
                break;
            }
        }
        if(pos) {
            cnt++;
        }
    }
    return cnt;
}

int main()
{
    int omap[100][100];
    int line[100];

    cin >> N >> L;

    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            cin >> omap[i][j];
        }
    }

    int cnt = 0;

    cnt += find(omap);

    int nmap[100][100];

    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            nmap[j][i] = omap[i][j];
        }
    }

    cnt += find(nmap);

    cout << cnt;
}