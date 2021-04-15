#include <iostream>
#include <cmath>

using namespace std;

int Turn(int num, int dir, int gear[][8], int pivot[4], bool left, bool right) {
    // Left
    if(num > 0 && left) {
        int lpivot = (pivot[num] + 6) % 8;
        int rpivot = (pivot[num - 1] + 2) % 8;

        if(gear[num][lpivot] != gear[num - 1][rpivot]) {
            Turn(num - 1, 0 - dir, gear, pivot, true, false);
        }
    }

    //Right
    if(num < 3 && right) {
        int rpivot = (pivot[num] + 2) % 8;
        int lpivot = (pivot[num + 1] + 6) % 8;

        if(gear[num][rpivot] != gear[num + 1][lpivot]) {
            Turn(num + 1, 0 - dir, gear, pivot, false, true);
        }
    }

    // Turn
    pivot[num] -= dir;
    pivot[num] = (pivot[num] + 8) % 8;

    return 1;
}

int main() {
    int gear[4][8];
    int K;

    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 8; j++) {
            char a;
            cin >> a;
            gear[i][j] = a - '0';
        }
    }

    cin >> K;

    int pivot[4] = {0, };

    for(int i = 0; i < K; i++) {
        int num, dir;
        cin >> num >> dir;

        num--;

        Turn(num, dir, gear, pivot, true, true);
    }

    int score = 0;

    for(int i = 0; i < 4; i++) {
        if(gear[i][pivot[i]] == 1) {
            score += pow(2, i);
        }
    }

    cout << score;
}