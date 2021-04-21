#include <iostream>
#include <vector>

using namespace std;

const int dr[4] = {-1, 1, 0, 0};
const int dc[4] = {0, 0, 1, -1};

int R, C, M;
vector<int> S(1, 0);
vector<int> D(1, 0);
vector<int> Z(1, 0);
int map[100][100] = {0, };
vector<int> cat;

int main() {
    cin >> R >> C >> M;
    for(int m = 0; m < M; m++) {
        int r, c, s, d, z;
        cin >> r >> c >> s >> d >> z;

        map[r-1][c-1] = m + 1;
        S.push_back(s);
        D.push_back(d - 1);
        Z.push_back(z);
    }

    for(int i = 0; i < C; i++) {
        // Catch
        for(int j = 0; j < R; j++) {
            if(map[j][i] != 0) {
                cat.push_back(map[j][i]);
                map[j][i] = 0;
                break;
            }
        }

        // Move
        vector<int> delayR;
        vector<int> delayC;
        vector<int> delayS;
        for(int r = 0; r < R; r++) {
            for(int c = 0; c < C; c++) {
                int shark = map[r][c];
                map[r][c] = 0;
                if(shark != 0) {
                    int newR = r + dr[D[shark]] * S[shark];
                    int newC = c + dc[D[shark]] * S[shark];
                    while(true) {
                        if (newR < 0)
                        {
                            D[shark] = 1;
                            newR = -newR;
                        }
                        else if (newR > R - 1)
                        {
                            D[shark] = 0;
                            newR = 2 * R - 2 - newR;
                        }
                        else if (newC < 0)
                        {
                            D[shark] = 2;
                            newC = -newC;
                        }
                        else if (newC > C - 1)
                        {
                            D[shark] = 3;
                            newC = 2 * C - 2 - newC;
                        }
                        else
                            break;
                    }

                    delayR.push_back(newR);
                    delayC.push_back(newC);
                    delayS.push_back(shark);
                }
            }
        }
        while(!delayS.empty()) {
            int r = delayR.back();
            int c = delayC.back();
            int shark = delayS.back();
            delayR.pop_back();
            delayC.pop_back();
            delayS.pop_back();
            if(Z[map[r][c]] < Z[shark]) {
                map[r][c] = shark;
            }
        }
    }
    int sum = 0;
    while(!cat.empty()) {
        sum += Z[cat.back()];
        cat.pop_back();
    }
    cout << sum;
}