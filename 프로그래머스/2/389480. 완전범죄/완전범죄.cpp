#include <string>
#include <vector>
#include <algorithm>

#define INF 0x3fffffff

using namespace std;

int solution(vector<vector<int>> infos, int n, int m) {
    vector<int> dp(m, INF);
    int sum = 0;
    for(auto a : infos) sum += a[0];
    dp[0] = sum;
    
    for(auto info : infos){
        int a = info[0], b = info[1];
        vector<int> tmp(m, INF);
        for(int i=0; i<m; i++){
            if(dp[i] == INF) continue;
            int new_idx = i + b;
            if(new_idx>=m) break;
            int new_val = dp[i] - a;
            tmp[new_idx] = min(dp[new_idx], new_val);
        }
        for(int i=0; i<m; i++){
            tmp[i] = min(dp[i], tmp[i]);
        }
        dp = tmp;
    }
    
    int answer = *min_element(dp.begin(), dp.end());
    return answer<n ? answer : -1;
}