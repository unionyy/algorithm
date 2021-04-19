#include <iostream>
#include <cmath>

using namespace std;

int N, L, R;
int A[50][50];
int B[50][50];

int Check(int r, int c, int b) {
    if(B[r][c] != 0) return 0;

    int sum = A[r][c];
    B[r][c] = b;

    if(r < N - 1) {
        int dif = abs(A[r][c] - A[r + 1][c]);
        if(dif >= L && dif <= R) {
            sum += Check(r + 1, c, b);
        }
    }
    if(r > 0) {
        int dif = abs(A[r][c] - A[r - 1][c]);
        if(dif >= L && dif <= R) {
            sum += Check(r - 1, c, b);
        }
    }

    if(c < N - 1) {
        int dif = abs(A[r][c] - A[r][c + 1]);
        if(dif >= L && dif <= R) {
            sum += Check(r, c + 1, b);
        }
    }
    if(c > 0) {
        int dif = abs(A[r][c] - A[r][c - 1]);
        if(dif >= L && dif <= R) {
            sum += Check(r, c - 1, b);
        }
    }

    return sum;
}

int main() {
    cin >> N >> L >> R;

    for(int i = 0; i < N; i++)
        for(int j = 0; j < N; j++)
            cin >> A[i][j];

    int cnt = 0;
    while(true) {
        for(int i = 0; i < N; i++) {
            for(int j = 0; j < N; j++) {
                B[i][j] = 0;
            }
        }

        int b = 1;
        for(int i = 0; i < N; i++) {
            for(int j = 0; j < N; j++) {
                int sum = Check(i, j, b);
                if(B[i][j] == b) {
                    if(A[i][j] != sum) {
                        int bnum = 0;
                        for(int k = 0; k < N; k++) {
                            for(int l = 0; l < N; l++) {
                                if(B[k][l] == b) {
                                    bnum++;
                                }
                            }
                        }
                        int np = sum / bnum;
                        for(int k = 0; k < N; k++) {
                            for(int l = 0; l < N; l++) {
                                if(B[k][l] == b) {
                                    A[k][l] = np;
                                }
                            }
                        }
                    }
                    b++;
                }
            }
        }

        if(b == N * N + 1) {
            cout << cnt;
            break;
        } else {
            cnt++;
        }
    }
}