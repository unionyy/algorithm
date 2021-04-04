/****** BAEKJOON 12100 *****/
/***** SAMSUNG SW TEST *****/
/** Solved Date 2020-10-12 */

#include <iostream>
#include <queue>
using namespace std;

queue<int**> bque;
queue<int>cntque;

void Conv(int *line, int n)
{
    int cnt = 0;
    for(int i=0; i<n-1; i++)
    {
        if(line[i] == 0) continue;
        else if(line[i+1] == 0){
            line[i+1] = line[i];
            line[i] = 0;
            continue;
        }else if(line[i] != line[i+1]) continue;
        else if(line[i] == line[i+1]){
            line[i] = line[i] + line[i];
            line[i+1] = 0;
            continue;
        }
    }
    
    for(int i=0; i<n; i++)
    {
        if(line[i] != 0)
        {
            line[cnt] = line[i];
            cnt++;

        }
    }

    for(int i=cnt; i<n; i++)
    {
        line[i] = 0;
    }
    return;
}

int Move(int **bod, int n, int ij, bool bs, int cnt)
{
    int **nbod = new int*[n];
    for(int i = 0; i<n;i++) nbod[i] = new int[n];
    int *line = new int[n];

    
    for(int i = 0; i < n; i++)
    {
        for(int j=0; j< n; j++)
        {
            int x, y;
            if(ij == 0)
            {
                y = i;
                if(bs) x = n-j-1;
                else x = j;
            }
            else
            {
                x = i;
                if(bs) y = n-j-1;
                else y = j;
            }
            line[j] = bod[x][y];
            
        }
        Conv(line, n);
        for(int j=0; j< n; j++)
        {
            int x, y;
            if(ij == 0)
            {
                y = i;
                if(bs) x = n-j-1;
                else x = j;
            }
            else
            {
                x = i;
                if(bs) y = n-j-1;
                else y = j;
            }

            nbod[x][y] = line[j];
            
        }
    }

    if(ij == 1 && !bs)
    {
        for(int i = 0; i<n; i++) delete [] bod[i];
        delete [] bod;

    }

    cnt++;

    if(cnt == 5)
    {
        int max = 0;
        for(int i = 0; i< n; i++)
        {
            for(int j = 0; j<n; j++)
            {
                if(nbod[i][j] > max) max = nbod[i][j];
            }
        }
        
        for(int i = 0; i<n; i++) delete [] nbod[i];
        delete [] nbod;

        return max;
    }
    else
    {
        bque.push(nbod);
        cntque.push(cnt);
        return 0;
    }
}

int main()
{
    cin.tie(NULL);
    ios::sync_with_stdio(false);

    int n;
    cin >> n;

    int **bod = new int*[n];
    for(int i = 0; i<n;i++) bod[i] = new int[n];
    
    for(int i = 0; i < n; i++)
    {
        for(int j=0; j<n; j++)
        {
            cin >> bod[i][j];
        }
    }

    bque.push(bod);
    cntque.push(0);
    int max = 0;
    while(!bque.empty())
    {
        int **nbod = bque.front();
        bque.pop();
        int cnt = cntque.front();
        cntque.pop();

        int tmp;
        tmp = Move(nbod, n, 0, true, cnt);
        if(tmp > max) max = tmp;
        tmp = Move(nbod, n, 0, false, cnt);
        if(tmp > max) max = tmp;
        tmp = Move(nbod, n, 1, true, cnt);
        if(tmp > max) max = tmp;
        tmp = Move(nbod, n, 1, false, cnt);
        if(tmp > max) max = tmp;
    }

    cout << max;
    return 0;
}