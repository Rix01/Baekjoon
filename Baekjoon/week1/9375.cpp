// 백준 9375
#include <bits/stdc++.h>
using namespace std;
int tc, n;  // test case, n
string name, group; // 의상, 종류
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    cin >> tc;
    for(int i =0; i<tc; i++){
        map<string, int> mp;    //**** map for문마다 초기화 해주려면 여기에 써줘야 함...
        cin >> n;
        // 의상 입력 받고 맵에 표기
        for(int j = 0; j<n; j++){
            cin >> name >> group;
            // 맵에 있다면
            if(mp.find(group) != mp.end()){
                mp[group]++;
            }
            // 맵에 없다면
            else{
                mp[group] = 1;
            }
        }
        long long day = 1;
        for(auto c:mp){
            day *= ((long long)c.second)+1;
        }
        day--;
        cout << day << "\n";
    }
    return 0;
}