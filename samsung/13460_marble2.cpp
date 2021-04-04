/****** BAEKJOON 13460 *****/
/***** SAMSUNG SW TEST *****/
/** Solved Date 2020-10-12 */

#include <iostream>
using namespace std;

char map[10][10];

int Right(int*, int*, int);
int Left(int*, int*, int);
int Up(int*, int*, int);
int Down(int*, int*, int);

int count = 0;

int Move(int *r, int *b, int cnt, int ij, bool bs)
{
    int *rb1, *rb2;
    int nr[2], nb[2];
    int stack = 0;

    nr[0] = r[0];
    nr[1] = r[1];
    nb[0] = b[0];
    nb[1] = b[1];

    if(nr[ij] > nb[ij] == bs)
    {
        rb1 = nr;
        rb2 = nb;
    }
    else
    {
        rb1 = nb;
        rb2 = nr;
    }

    int x, y;
    
    
    
    // rb1
    while(true)
    {
        if(bs)
        {
            x = rb1[0] + 1 - ij;
            y = rb1[1] + ij;
        }
        else
        {
            x = rb1[0] - 1 + ij;
            y = rb1[1] - ij;
        }

        if(map[x][y] == '#')
        {
            break;
        }
        else if(map[x][y] == '.')
        {
            if(bs) rb1[ij]++;
            else rb1[ij]--;
            continue;
        }
        else if(map[x][y] == 'O')
        {
            rb1[ij] = 0;
            if(rb1 == nr)
            {
                stack++;
                break;
            }
            else
            {
                return 11; //fail
            }
            
        }
        else{
            cout << x << "," << y << ": " << map[x][y] << "\n";
            return 11;
        }
        cout << "1";
    }
    
    

    // rb2
    while(true)
    {
        if(bs)
        {
            x = rb2[0] + 1 - ij;
            y = rb2[1] + ij;
        }
        else
        {
            x = rb2[0] - 1 + ij;
            y = rb2[1] - ij;
        }
        if(map[x][y] == 'O')
        {
            if(rb2 == nr)
            {
                return cnt+1;
            }
            else
            {
                return 11; //fail
            }
            
        }
        else if(rb1[0] == x && rb1[1] == y)
        {
            break;
        }
        if(map[x][y] == '#')
        {
            if(stack == 1) return cnt+1;
            break;
        }
        else if(map[x][y] == '.')
        {
            if(bs) rb2[ij]++;
            else rb2[ij]--;
            continue;
        } 
        else{
            cout << x << "," << y << ": " << map[x][y] << "\n";
            return 11;
        }
        cout << "2";
    }

    if(cnt > 9) return 11;

    int up = Move(nr, nb, cnt+1, (ij+1)%2, true);
    int down = Move(nr, nb, cnt+1, (ij+1)%2, false);

    if (up < down) return up;
    else return down;

}

int main()
{
    int n, m;

    cin >> n >> m;

    
    int r[2];
    int b[2];

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            char a;
            cin >> a;
            if(a == 'R')
            {
                r[0] = i;
                r[1] = j;
                map[i][j] = '.';
            }
            else if(a == 'B')
            {
                b[0] = i;
                b[1] = j;
                map[i][j] = '.';
            }
            else map[i][j] = a;
        }
    }

    int min;

    int right = Move(r, b, 0, 1, true);
    int left = Move(r, b, 0, 1, false);
    int up = Move(r, b, 0, 0, true);
    int down = Move(r, b, 0, 0, false);

    min = right;
    if(min > left) min = left;
    if(min > up) min = up;
    if(min > down) min = down;

    if(min == 11) cout << -1;
    else cout << min;

    return 0;

}