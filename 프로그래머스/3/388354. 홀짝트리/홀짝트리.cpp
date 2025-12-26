#include <string>
#include <vector>
#include <map>

using namespace std;

map<int, vector<int>> graph;

int det(int parent, int current, bool kind);

vector<int> solution(vector<int> nodes, vector<vector<int>> edges) {
    for(auto edge : edges){
        graph[edge[0]].push_back(edge[1]);
        graph[edge[1]].push_back(edge[0]);
    }
    
    vector<int> answer(2,0);
    for(auto node : nodes){
        int result = det(0, node, 0);
        if(result >=0) answer[result]++;
    }
    
    return answer;
}

int det(int parent, int current, bool kind){
    int child = graph[current].size();
    if(parent != 0) child--;
    else kind = (current %2 == child%2);
    
    if((current%2 == child%2) != kind) return -1;
    for(int next : graph[current]){
        if(next == parent) continue;
        if(det(current, next, kind)<0) return -1;
    }
    return !kind;
}