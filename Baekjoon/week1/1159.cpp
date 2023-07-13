// 카운팅은 map 또는 배열
#include <bits/stdc++.h>
using namespace std;
int n, cnt[26];
string name, ret;
int main(){
    cin >> n;
    for(int i = 0; i<n; i++){
        cin >> name;
        cnt[name[0]-'a']++;
    }
    for(int i = 0; i<26; i++){
        if(cnt[i]>=5) ret += (i+'a');
    }
    // ret에 들어간 알파벳이 있으면 그것을 출력
    if(ret.size()>0) cout << ret <<"";
    // 없으면 PREDAJA 출력
    else cout << "PREDAJA" <<"";
    return 0;
}