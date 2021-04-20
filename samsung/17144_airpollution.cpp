#include <iostream>

using namespace std;

int R, C, T;
int A[50][50];

int U = -1, D = -1;

int main() {
    cin >> R >> C >> T;

    for(int r = 0; r < R; r++) {
        for(int c = 0; c < C; c++) {
            cin >> A[r][c];
            if(A[r][c] == -1) {
                if(U == -1) {
                    U = r;
                } else {
                    D = r;
                }
            }
        }
    }

    for(int t = 0; t < T; t++) {
        int newA[50][50] = {0, };

        // Diffusion
        for(int r = 0; r < R; r++) {
            for(int c = 0; c < C; c++) {
                int pol = A[r][c];
                if(pol == -1) {
                    newA[r][c] = -1;
                } else if(pol != 0) {
                    int dif = pol / 5;
                    int cnt = 0;
                    if(r - 1 >= 0 && A[r-1][c] != -1) {
                        cnt++;
                        newA[r-1][c] += dif;
                    }
                    if(c - 1 >= 0 && A[r][c-1] != -1) {
                        cnt++;
                        newA[r][c-1] += dif;
                    }
                    if(r + 1 < R && A[r+1][c] != -1) {
                        cnt++;
                        newA[r+1][c] += dif;
                    }
                    if(c + 1 < C && A[r][c+1] != -1) {
                        cnt++;
                        newA[r][c+1] += dif;
                    }
                    pol -= cnt * dif;
                    newA[r][c] += pol;
                }
            }
        }

        // Flow
        for(int i = U - 2; i >= 0; i--) {
            newA[i+1][0] = newA[i][0];
        }
        for(int i = D + 2; i < R; i++) {
            newA[i-1][0] = newA[i][0];
        }

        for(int i = 0; i < C - 1; i++) {
            newA[0][i] = newA[0][i+1];
            newA[R-1][i] = newA[R-1][i+1];
        }
        
        for(int i = 0; i < U; i++) {
            newA[i][C-1] = newA[i+1][C-1];
        }
        for(int i = R - 1; i > D; i--) {
            newA[i][C-1] = newA[i-1][C-1];
        }

        for(int i = C - 1; i > 1; i--) {
            newA[U][i] = newA[U][i-1];
            newA[D][i] = newA[D][i-1];
        }

        newA[U][1] = 0;
        newA[D][1] = 0;

        for(int r = 0; r < R; r++) {
            for(int c = 0; c < C; c++) {
                A[r][c] = newA[r][c];
            }
        }
    }

    int sum = 2;
    for(int r = 0; r < R; r++) {
        for(int c = 0; c < C; c++) {
            sum += A[r][c];
        }
    }
    cout << sum;
}