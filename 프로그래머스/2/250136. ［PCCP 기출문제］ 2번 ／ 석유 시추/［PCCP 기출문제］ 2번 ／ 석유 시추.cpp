#include <string>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

int di[4] = {0,1,0,-1};
int dj[4] = {1,0,-1,0};

vector<vector<int>> land;
int r, c;

void exec_dfs(int i, int j, vector<vector<bool>> &is_visited, vector<int> &col_count);
int dfs(int i, int j, set<int> &cols, vector<vector<bool>> &is_visited);

int solution(vector<vector<int>> land_) {
    land = land_;
    r = land.size(), c = land[0].size();
    vector<vector<bool>> is_visited(r,vector<bool>(c,false));
    vector<int> col_count(c,0);
    
    for(int i=0; i<r; i++){
        for(int j=0; j<c; j++){
            exec_dfs(i,j,is_visited, col_count);
        }
    }
    
    return *max_element(col_count.begin(), col_count.end());
}

void exec_dfs(int i, int j, vector<vector<bool>> &is_visited, vector<int> &col_count){
    if(land[i][j] == 0) return;
    if(is_visited[i][j]) return;
    
    set<int> cols;
    int result = dfs(i,j,cols,is_visited);
    for(auto col : cols){
        col_count[col] += result;
    }
}

int dfs(int i, int j, set<int> &cols, vector<vector<bool>> &is_visited){
    if(is_visited[i][j]) return 0;
    if(land[i][j] == 0) return 0;
    is_visited[i][j] = true;
    cols.insert(j);
    int result = 1;
    for(int dir=0; dir<4; dir++){
        int ni = i + di[dir];
        int nj = j + dj[dir];
        if(ni<0 || ni>=r || nj<0 || nj>=c) continue;
        if(is_visited[ni][nj]) continue;
        if(land[ni][nj] == 0) continue;
        
        result += dfs(ni, nj, cols, is_visited);
    }
    return result;
}