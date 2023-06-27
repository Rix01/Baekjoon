// 백준 2979
#include <bits/stdc++.h>
using namespace std;
int time_table[101];
int t_a, t_l, max_t =0;   // 트럭 도착한 시간 떠난 시간
int money = 0;
int main(){
    int a, b, c;
    cin >> a >> b >> c;
    // 도착한 시간과 떠난 시간
    for(int i = 0; i<3; i++){
        cin >> t_a >> t_l;
        if(t_l > max_t) max_t = t_l;
        for(int j = t_a; j<t_l; j++){
            time_table[j] +=1;
        }
    }
    for(int i = 1; i<max_t; i++){
        if(time_table[i]==1) money += a;
        else if(time_table[i]==2) money += 2* b;
        else if(time_table[i]==3) money += 3* c;
    }
    cout << money << "\n";
    return 0;
}