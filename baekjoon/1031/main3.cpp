#include <iostream>

using namespace std;

#define MAX_N 50

int N, M;
int gamesN[MAX_N], gamesM[MAX_N];

int resS[MAX_N], resT[MAX_N], res[MAX_N][MAX_N];
bool checkN[MAX_N], checkM[MAX_N];

bool dfsM(int m, int dst);
bool dfsN(int n, int dst) {
    checkN[n] = true;
    for(int i = 0; i < M; i++) {
        if(checkM[i] || res[n][i] == 0) continue;
        res[n][i]--;
        if(dfsM(i, dst)) {
            checkN[n] = false;
            return true;
        }
        res[n][i]++;
    }
    checkN[n] = false;
    return false;
}

bool dfsM(int m, int dst) {
    checkM[m] = true;
    if(m == dst) {
        checkM[m] = false;
        return true;
    }
    if(resT[m] > 0) {
        resT[m]--;
        checkM[m] = false;
        return true;
    }
    for(int i = 0; i < N; i++) {
        if(checkN[i] || res[i][m] == 1) continue;
        res[i][m]++;
        if(dfsN(i, dst)) {
            checkM[m] = false;
            return true;
        }
        res[i][m]--;
    }
    checkM[m] = false;
    return false;
}

int main() {
    // Input
    cin >> N >> M;
    for(int i = 0; i < N; i++) cin >> gamesN[i];
    for(int i = 0; i < M; i++) cin >> gamesM[i];

    // Verify
    int sum = 0;
    for(int i = 0; i < N; i++) sum += gamesN[i];
    for(int i = 0; i < M; i++) sum -= gamesM[i];
    if(sum != 0) {
        cout << -1;
        return 0;
    }

    /** Maximum Flow */
    // Init
    for(int i = 0; i < N; i++) {
        resS[i] = gamesN[i];
        checkN[i] = false;
    }
    for(int i = 0; i < M; i++) {
        resT[i] = gamesM[i];
        checkM[i] = false;
    }
    for(int i = 0; i < N; i++)
        for(int j = 0; j < M; j++) res[i][j] = 1;

    // Fine Maximum Flow
    for(int i = 0; i < N; i++) {
        while(resS[i] > 0) {
            if(dfsN(i, -1)) {
                resS[i]--;
            }
            else {
                cout << -1;
                return 0;
            }
        }
    }

    /** Sort */
    for(int i = 0; i < N; i++) {
        checkN[i] = true;
        for(int j = 0; j < M; j++) {
            if(res[i][j] == 1) continue;
            for(int k = j+1; k < M; k++) {
                if(res[i][k] == 0) continue;
                if(dfsM(k, j)) {
                    res[i][j] = 1;
                    break;
                }
            }
        }
    }

    // Print
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < M; j++) {
            if(res[i][j] == 0) cout << 1;
            else cout << 0;
            cout << ' ';
        }
        cout << '\n';
    }

    return 0;
}