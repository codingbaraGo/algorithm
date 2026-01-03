#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int solution(int h1, int m1, int s1, int h2, int m2, int s2) {
    int answer = 0;
    vector<double> m;
    vector<double> h;
    vector<double> total;
    
    for(double s=0; s<59; s+=1.0){
        m.push_back(s * (60 + 60.0/59.0));
    }
    for(double s=1; ; s+=1.0){
        if(s * (60 + 60.0/719.0) >= 12*3600) break;
        total.push_back(s * (60 + 60.0/719.0));
        total.push_back(s * (60 + 60.0/719.0) + 12 * 3600);
    }
    
    for(int i=0; i<24; i++){
        for(auto a : m)
            total.push_back(a+i*3600);
    }
    
    sort(total.begin(), total.end());
    double start = h1*3600 + m1*60 + s1;
    double end = h2*3600 + m2*60 + s2;
    
    for(auto a : total){
        if(start > a) continue;
        if(end < a) break;
        answer++;
    }
    
    return answer;
}