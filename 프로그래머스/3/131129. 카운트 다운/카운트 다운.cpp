#include <string>
#include <vector>

using namespace std;

pair<int, int> best_pair(pair<int, int> p1, pair<int, int> p2);

vector<int> solution(int target) {
    vector<pair<int, int>> cost_pair(30001, {0,0});
    for(int i=1; i<=20; i++){
        cost_pair[i] = {1,1};
        cost_pair[i*2] = {1,0};
        cost_pair[i*3] = {1,0};
    }
    cost_pair[50] = {1,1};
    
    for(int i=2; i<=30000; i++){
        if(!(cost_pair[i].first == 0 && cost_pair[i].second == 0)) continue;
        cost_pair[i] = {cost_pair[1].first + cost_pair[i-1].first, cost_pair[1].second + cost_pair[i-1].second};
        for(int j=1; j<=i/2; j++){
            cost_pair[i] = best_pair(cost_pair[i], {cost_pair[j].first + cost_pair[i-j].first, cost_pair[j].second + cost_pair[i-j].second});
        }
    }
    
    int t1 = target%30000;
    int r1 = target/30000;
    pair<int,int> ans1 = cost_pair[t1];
    ans1.first += r1*500;
    
    int t2 = target%27000;
    int r2 = target/27000;
    pair<int,int> ans2 = cost_pair[t2];
    ans2.first += r2*450;
    
    pair<int, int> ans = best_pair(ans1, ans2);
    return vector<int> ({ans.first, ans.second});
}

pair<int, int> best_pair(pair<int, int> p1, pair<int, int> p2){
    if(p1.first < p2.first) return p1;
    else if (p1.first > p2.first) return p2;
    if(p1.second > p2.second) return p1;
    return p2;
}