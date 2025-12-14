#include <string>
#include <vector>

using namespace std;

extern string submit(int);

struct Node {
    string str;
    int strike;
    int ball;
};

vector<Node> nodes;

bool check_dup(int n);
bool det_all(int n);
bool det(string str, int idx);

int solution(int n) {
    int cnt = 0;
    for(int i = 1000; i <= 9999; i++) {
        if(!check_dup(i)) continue;
        if(!det_all(i)) continue;
        if(cnt == 6) return i;
        string result = submit(i);
        cnt++;
        if (result == "4S 0B") return i;
        int s = result[0] - '0', b = result[3] - '0';
        nodes.push_back({to_string(i), s, b});
    }
    return 0;
}

bool check_dup(int n){
    string num = to_string(n);
    for(int i=0; i<4; i++){
        if(num[i] == '0') return false;
        for(int j=i+1; j<4; j++){
            if(num[i] == num[j]) return false;
        }
    }
    return true;
}

bool det_all(int n){
    string num = to_string(n);
    for(int i=0; i<nodes.size(); i++){
        if(!det(num, i)) return false;
    }
    return true;
}

bool det(string str, int idx){
    auto node = nodes[idx];
    int strike = 0, ball = 0;
    for(int i=0; i<4; i++){
        for(int j=0; j<4; j++){
            if(str[i] != node.str[j]) continue;
            if(i == j) strike++;
            else ball++;
        }
    }
    return (strike == node.strike) && (ball == node.ball);
}