#include <string>
#include <vector>
#include <algorithm>

using namespace std;

vector<vector<int>> subnode;
vector<int> cursor;
vector<int> target(1,0);
vector<int> edge_seq(0);
int target_count = 0;

void init(vector<vector<int>> &edges, vector<int> target_);
bool visit(int idx);

vector<int> solution(vector<vector<int>> edges, vector<int> target_) {
    init(edges, target_);
    vector<int> answer;
    while(true){
        if(visit(1) == false) return {-1};
        if(target_count == 0) break;
    }
    
    for(auto n : edge_seq){
        int t = target[n];
        int v = cursor[n];
        int val = 0;
        if(v*3 == t) val = 3;
        else if (v*3 - 1 == t) val = 2;
        else val = 1;
        cursor[n]--;
        target[n] -= val;
        answer.push_back(val);
        
    }
    
    return answer;
}

void init(vector<vector<int>> &edges, vector<int> target_){
    subnode.assign(edges.size()+2,vector<int>(0));
    cursor.assign(edges.size()+2, 0);
    target.insert(target.end(), target_.begin(), target_.end());
    for(auto t : target) if(t>0) target_count++;
    for(auto e : edges){
        subnode[e[0]].push_back(e[1]);
        sort(subnode[e[0]].begin(), subnode[e[0]].end());
    }
}

bool visit(int idx){
    int length = subnode[idx].size();
    int visited = cursor[idx];
    cursor[idx]++;
    if(length == 0){    //leaf node
        edge_seq.push_back(idx);
        if(target[idx] > visited*3 && target[idx] <= (visited+1)*3) target_count--;
        if(target[idx] < visited+1) return false;
        
    } else{ //none - leaf node
        int next_idx = subnode[idx][visited%length];
        return visit(next_idx);
    }
    return true;
}
