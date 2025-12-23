#include <string>
#include <vector>

#define DESTROY     0
#define CONSTRUCT  1
#define COL     0
#define BO      1

using namespace std;

bool check_delete_col(int x, int y, vector<vector<bool>> &bo, vector<vector<bool>> &col);
bool check_delete_bo(int x, int y, vector<vector<bool>> &bo, vector<vector<bool>> &col);
bool check_col(int x, int y, vector<vector<bool>> &bo, vector<vector<bool>> &col);
bool check_bo(int x, int y, vector<vector<bool>> &bo, vector<vector<bool>> &col);

int n;

vector<vector<int>> solution(int n_, vector<vector<int>> build_frame) {
    n = n_;
    vector<vector<int>> answer;
    vector<vector<bool>> bo(n+1, vector<bool>(n+1,false));
    vector<vector<bool>> col(n+1, vector<bool>(n+1,false));
    
    for(auto frame : build_frame){
        int type = frame[2], action = frame[3];
        int x=frame[0], y=frame[1];
        if(action==DESTROY){
            if(type==COL){
                bool tmp = col[x][y];
                col[x][y]=false;
                if(!check_delete_col(x,y,bo,col)) col[x][y] = tmp;
            } else if (type==BO){
                bool tmp = bo[x][y];
                bo[x][y]=false;
                if(!check_delete_bo(x,y,bo,col)) bo[x][y] = tmp;
            }
        } else if (action==CONSTRUCT){
            if(type==COL){
                if(check_col(x,y,bo,col)) col[x][y] = true;
            } else if (type==BO){
                if(check_bo(x,y,bo,col)) bo[x][y] = true;
            }
        }
    }

    for(int x=0; x<=n; x++){
        for(int y=0; y<=n; y++){
            if(col[x][y]) answer.push_back({x,y,0});
            if(bo[x][y]) answer.push_back({x,y,1});
        }
    }
    
    return answer;
}

bool check_delete_col(int x, int y, vector<vector<bool>> &bo, vector<vector<bool>> &col){
    if(y==n) return true;
    if(col[x][y+1] && !check_col(x,y+1,bo,col)) return false;
    if(bo[x][y+1] && !check_bo(x,y+1,bo,col)) return false;
    if(x-1>=0 && bo[x-1][y+1] && !check_bo(x-1,y+1,bo,col)) return false;
    return true;
}

bool check_delete_bo(int x, int y, vector<vector<bool>> &bo, vector<vector<bool>> &col){
    if(col[x][y] && !check_col(x,y,bo,col)) return false;
    if(x+1<=n && col[x+1][y] && !check_col(x+1,y,bo,col)) return false;
    if(x-1>=0 && bo[x-1][y] && !check_bo(x-1,y,bo,col)) return false;
    if(x+1<=n && bo[x+1][y] && !check_bo(x+1,y,bo,col)) return false;
    return true;
}

bool check_col(int x, int y, vector<vector<bool>> &bo, vector<vector<bool>> &col){
    if(y==0) return true;
    if(y-1>=0 && col[x][y-1]) return true;
    if(x-1>=0 && bo[x-1][y]) return true;
    return bo[x][y];
}

bool check_bo(int x, int y, vector<vector<bool>> &bo, vector<vector<bool>> &col){
    if(y-1>=0 && col[x][y-1]) return true;
    if(x+1<=n && y-1 >= 0 && col[x+1][y-1]) return true;
    if(x-1>=0 && x+1<=n && bo[x-1][y] && bo[x+1][y]) return true;
    return false;
}