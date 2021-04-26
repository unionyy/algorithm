#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int ParseTime(string time) {
    int sum = 0;
    // Hour
    int h = stoi(time.substr(0, 2));
    sum += h * 3600;
    
    // Minute
    int m = stoi(time.substr(3, 2));
    sum += m * 60;
    
    // Sec
    int s = stoi(time.substr(6, 2));
    sum += s;
    
    return sum;
}

string Encode(int time) {
    int h = time / 3600;
    int m = time / 60 % 60;
    int s = time % 60;
    
    string str = "";
    str += (h / 10) + '0';
    str += (h % 10) + '0';
    str += ':';
    str += (m / 10) + '0';
    str += (m % 10) + '0';
    str += ':';
    str += (s / 10) + '0';
    str += (s % 10) + '0';
    
    return str;
}

string solution(string play_time, string adv_time, vector<string> logs) {
    string answer = "";
    int ptime = ParseTime(play_time);
    int atime = ParseTime(adv_time);
    
    vector<int> stimes;
    vector<int> etimes;
    
    for(string log : logs) {
        stimes.push_back(ParseTime(log.substr(0, 8)));
        etimes.push_back(ParseTime(log.substr(9, 8)));
    }
    
    sort(stimes.begin(), stimes.end());
    sort(etimes.begin(), etimes.end());

    long max = 0;
    int ans = 0;
    
    int scnt = 0;
    int ecnt = 0;
    int stk = 0;
    for(int i = 0; i < atime; i++) {
        while(scnt < stimes.size() && stimes[scnt] <= i) {
            stk++;
            scnt++;
        }
        while(ecnt < etimes.size() && etimes[ecnt] <= i) {
            stk--;
            ecnt++;
        }
        max += stk;
    }
    
    long maxx = max;
    
    int sscnt = 0;
    int eecnt = 0;
    for(int i = atime; i < ptime; i++) {
        while(sscnt < stimes.size() && stimes[sscnt] <= i - atime) {
            stk--;
            sscnt++;
        }
        while(eecnt < etimes.size() && etimes[eecnt] <= i - atime) {
            stk++;
            eecnt++;
        }
        
        while(scnt < stimes.size() && stimes[scnt] <= i) {
            stk++;
            scnt++;
        }
        while(ecnt < etimes.size() && etimes[ecnt] <= i) {
            stk--;
            ecnt++;
        }
        max += stk;
        if(max > maxx) {
            maxx = max;
            ans = i - atime + 1;
        }
    }
    
    answer = Encode(ans);
    
    return answer;
}