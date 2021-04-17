/****** BAEKJOON 15685 *****/
/***** SAMSUNG SW TEST *****/
/** Solved Date 2021-04-16 */

#include <iostream>
#include <vector>

using namespace std;

const int dx[4] = {1, 0, -1, 0};
const int dy[4] = {0, -1, 0, 1};

int main() {
    int N;
    cin >> N;

    bool map[101][101] = {false, };

    for(int i = 0; i < N; i++) {
        int x, y, d, g;

        cin >> x >> y >> d >> g;

        vector<int> path;
        path.push_back(d);
        map[x][y] = true;

        for(int j = 0; j < g; j++) {
            int clen = path.size();
            for(int k = 0; k < clen; k++) {
                path.push_back((path[clen - 1 - k] + 1) % 4);
            }
        }

        int n = path.size();
        for(int j = 0; j < n; j++) {
            int dir = path[j];
            
            x += dx[dir];
            y += dy[dir];
            map[x][y] = true;
        }
    }

    // Find Rect
    int cnt = 0;
    for(int i = 0; i < 100; i++) {
        for(int j = 0; j < 100; j++) {
            if(map[i][j] && map[i][j+1] && map[i+1][j] && map[i+1][j+1]) {
                cnt++;
            }
        }
    }
    cout << cnt;
}