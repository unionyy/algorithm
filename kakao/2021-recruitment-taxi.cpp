#include <string>
#include <vector>
#include <queue>

using namespace std;

const int INF = 10000000;
int map[200][200];

void Dijk(int start, int n, vector<int>& dis) {
    dis[start] = 0;
    priority_queue<pair<int, int>> pq;
    pq.push(make_pair(start, 0));
    
    while(!pq.empty()) {
        int next = pq.top().first;
        int cdis = - pq.top().second;
        pq.pop();
        
        if(cdis > dis[next]) continue;
        
        for(int i = 0; i < n; i++) {
            int ndis = cdis + map[i][next];
            if(dis[i] > ndis) {
                dis[i] = ndis;
                pq.push(make_pair(i, - ndis));
            }
        }
    }
    return;
}

int solution(int n, int s, int a, int b, vector<vector<int>> fares) {
    int answer = INF;
    
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            map[i][j] = INF;
            if(i == j) {
                map[i][j] = 0;
            }
        }
    }
    
    for(auto fare : fares) {
        int r = fare[0] - 1;
        int c = fare[1] - 1;
        int dis = fare[2];
        map[r][c] = dis;
        map[c][r] = dis;
    }
    
    vector<vector<int>> dis(3, vector<int>(n, INF));
    Dijk(s - 1, n, dis[0]);
    Dijk(a - 1, n, dis[1]);
    Dijk(b - 1, n, dis[2]);
    
    for(int i = 0; i < n; i++) {
        int sum = 0;
        for(auto elem : dis) {
            sum += elem[i];
        }
        if(sum < answer) answer = sum;
    }
    
    return answer;
}