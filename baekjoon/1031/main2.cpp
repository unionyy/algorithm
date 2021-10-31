#include <iostream>
#include <algorithm>

using namespace std;

#define MAX_N 50

int N, M;
int gamesN[MAX_N], gamesM[MAX_N];
int table[MAX_N][MAX_N];
int tmp[MAX_N];

int main() {
    // Input
    cin >> N >> M;
    for(int i = 0; i < N; i++) cin >> gamesN[i];
    for(int i = 0; i < M; i++) cin >> gamesM[i];

    // Make Talbe
    for(int i = 0; i < N; i++) {
        for(int j = i + 1; j < N; j++) tmp[j] = gamesN[j];
        int leftGame = gamesN[i];
        int zeroM = 0;
        
        for(int j = 0; j < M; j++) {
            if(gamesM[j] == 0) zeroM++;
        }

        for(int j = 0; j < M; j++) {
            int zeroN = 0;
            for(int j = i + 1; j < N; j++) {
                if(tmp[j] == 0) zeroN++;
            }
            if(leftGame == 0) {
                table[i][j] = 0;
            }
            else if(gamesM[j] == 0) {
                table[i][j] = 0;
                zeroM--;
            }
            // Must Fill
            else if((leftGame == M - j - zeroM) || (gamesM[j] == N - i - zeroN)) {
                table[i][j] = 1;
                leftGame--;
                gamesM[j]--;
            }
            else {
                table[i][j] = 0;
            }

            sort(tmp + i + 1, tmp + N, greater<int>());
            for(int k = i + 1; k < i + 1 + gamesM[j]; k++) tmp[k]--;
        }
    }

    // Verify
    bool pos = true;
    for(int i = 0; i < N; i++) {
        int sum = 0;
        for(int j = 0; j < M; j++) {
            sum += table[i][j];
        }
        if(sum != gamesN[i]) {
            pos = false;
            break;
        }
    }
    for(int i = 0; i < M; i++) {
        if(gamesM[i] != 0) {
            pos = false;
            break;
        }
    }

    if(pos) {
        for(int i = 0; i < N; i++) {
            for(int j = 0; j < M; j++) {
                cout << table[i][j];
                cout << ' ';
            }
            cout << '\n';
        }
    }
    else {
        cout << "-1" << endl;
    }
    

    return 0;
}