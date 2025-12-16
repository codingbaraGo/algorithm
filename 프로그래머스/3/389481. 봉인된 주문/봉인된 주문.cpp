#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

long long to_numeric(string str);
string to_str(long long num);

string solution(long long n, vector<string> bans) {
    vector<long long> num_vec(0);
    for(auto str : bans){
        num_vec.push_back(to_numeric(str));
    }
    sort(num_vec.begin(), num_vec.end());
    for(auto num : num_vec){
        if(num > n) break;
        n++;
    }
    return to_str(n);
}

long long to_numeric(string str){
    int length = str.size();
    long long num = 0;
    for(int i = 0; i<length; i++){
        char c = str[i];
        int constant = c - 'a' + 1;
        int expo = length - i - 1;
        num += constant * pow(26,expo);
    }
    return num;
}

string to_str(long long num){
    string str;
    for(int i=0; num>0;i++){
        int rest = num%26;
        if(rest == 0) rest = 26;
        char c = 'a' + rest -1;
        num -= rest;
        num /= 26;
        str.insert(0,1,c);
    }
    return str;
}