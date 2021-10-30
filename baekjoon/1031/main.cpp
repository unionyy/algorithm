#include <iostream>
#include <algorithm>

using namespace std;

#define MAX_N 50

int N, M;
int gamesN[MAX_N], gamesM[MAX_N];
int table[MAX_N][MAX_N];

bool dfs(int done) {
    // check
    for(int i = 0; i < M; i++) {
        int sum = 0;
        for(int j = 0; j < done; j++) sum += table[j][i];

        if(sum > gamesM[i]) return false;
    }

    // End
    if(done == N) return true;

    // Estimate A Row
    int tmpTable[MAX_N];
    int games = gamesN[done];
    for(int i = 0; i < M - games; i++) tmpTable[i] = 0;
    for(int i = M - games; i < M; i++) tmpTable[i] = 1;

    do {
        for(int i = 0; i < M; i++) table[done][i] = tmpTable[i];
        if(dfs(done + 1)) return true;
    }
    while(next_permutation(tmpTable, tmpTable + M));

    return false;
}

int main() {
    // Input
    cin >> N >> M;
    for(int i = 0; i < N; i++) cin >> gamesN[i];
    for(int i = 0; i < M; i++) cin >> gamesM[i];

    // Init
    for(int i = 0; i < N; i++) for(int j = 0; j < M; j++) table[i][j] = 0;

    if(dfs(0)) {
        for(int i = 0; i < N; i++) {
            for(int j = 0; j < M; j++) {
                cout << table[i][j];
                cout << ' ';
            }
            cout << '\n';
        }
    }
    else cout << "-1";

    return 0;
}