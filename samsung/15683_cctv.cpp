/****** BAEKJOON 15683 *****/
/***** SAMSUNG SW TEST *****/
/** Solved Date 2021-04-16 */

#include <iostream>

using namespace std;

const int dx[4] = {0, 1, 0, -1};
const int dy[4] = {-1, 0, 1, 0};
const int cctv[5][4] = {
    {0, 0, 0, 0},
    {0, 2, 0, 0},
    {0, 1, 0, 0},
    {0, 1, 2, 0},
    {0, 1, 2, 3}
};

int N, M;

int ans = 64;

int dfs(int map[][8], int x, int y, bool first) {
    for(int i = x; i < N; i++) {
        for(int j = 0; j < M; j++) {
            if(i == x && j <= y && !first) continue;

            if(0 < map[i][j] && map[i][j] < 6) {
                for(int k = 0; k < 4; k++) {
                    int tmap[8][8];
                    // Copy map
                    for(int ii = 0; ii < N; ii++) {
                        for(int jj = 0; jj < M; jj++) {
                            tmap[ii][jj] = map[ii][jj];
                        }
                    }
                    for(int d = 0; d < 4; d++) {
                        int dir = (k + cctv[map[i][j] - 1][d]) % 4;
                        for(int l = 0; l < 8; l++) {
                            if((i + dx[dir] * l) >= N || (i + dx[dir] * l) < 0 || (j + dy[dir] * l) >= M || (j + dy[dir] * l) < 0) {
                                break;
                            }
                            if(map[i + dx[dir] * l][j + dy[dir] * l] == 0) {
                                tmap[i + dx[dir] * l][j + dy[dir] * l] = 7;
                            } else if(map[i + dx[dir] * l][j + dy[dir] * l] == 6) {
                                break;
                            }
                        }
                    }
                    
                    dfs(tmap, i, j, false);
                }
                return 1;
            }
        }
    }

    // Count
    int cnt = 0;
    for(int i = 0; i < N; i++) {
        for(int j = 0 ; j < M; j++) {
            if(map[i][j] == 0) {
                cnt++;
            }
        }
    }
    if (cnt < ans) {
        ans = cnt;
    }
    return 1;
}

int main() {
    int map[8][8];

    // INPUT
    cin >> N >> M;
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < M; j++) {
            cin >> map[i][j];
        }
    }

    dfs(map, 0, 0, true);

    cout << ans;
}