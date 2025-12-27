#include <string>
#include <vector>
#include <queue>
#include <map>

using namespace std;

map<int, vector<vector<int>>> req_map;
vector<vector<pair<int, int>>> waits;
int min_wait = 1000000000;
int k, n;

void rec(int type, int total_t, int total_wait);
int func(int t, int type);

int solution(int k_, int n_, vector<vector<int>> reqs) {
    k = k_, n = n_;
    waits.assign(k+1, vector<pair<int, int>>(0));
    
    for(auto req : reqs){
        req_map[req[2]].push_back({req[0], req[1]});
    }
    
    for(int type = 1; type <= k; type++){
        for(int t=1; t<=n-k+1; t++){
            waits[type].push_back({t, func(t,type)});
        }
    }
    
    rec(1, 0, 0);
        
    return min_wait;
}

void rec(int type, int total_t, int total_wait){
    if(type > k){
        if(total_t != n) return;
        min_wait = min(min_wait, total_wait);
        return;
    }
    for(auto wait : waits[type]){
        int t = wait.first, wait_time = wait.second;
        if(n - (total_t + t) < k - type) continue;
        rec(type+1, total_t + t, total_wait + wait_time);
    }
}

int func(int t, int type){
    int total_wait = 0;
    priority_queue<int,vector<int>, greater<int>> pq;
    for(auto req : req_map[type]){
        int arrival_time = req[0];
        if(t==0){
            int prev_end = pq.top();
            int start_time = max(prev_end, arrival_time);
            int end_time = start_time + req[1];
            pq.pop();
            total_wait += max(0, prev_end - arrival_time);
            pq.push(end_time);
        } else{
            t--;
            pq.push(req[0] + req[1]);
        }
    }
    return total_wait;
}