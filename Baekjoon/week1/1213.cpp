#include <bits/stdc++.h>
using namespace std;
int cnt[200], flag=0;
string s, ret;
char c;
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    cin >> s;
    // 카운팅 배열 채우기
    for(char a:s) cnt[a]++;
    // 내림차순
    for(int i = 'Z'; i>='A'; i--){
        if(cnt[i]){
            // 홀수 개수가 하나 있으면
            // 하나까지는 괜찮음. 2개부터 안 됨.
            if(cnt[i] & 1){
                c = char(i);
                flag++;
                cnt[i]--;
            }
            // 홀수 개수가 2개이면
            if(flag == 2) break;
            for(int j = 0; j<cnt[i]; j+=2){
                // 앞뒤로 붙이기
                ret = char(i) + ret;
                ret += char(i);
            }
        }
    }
    // 홀수 개수가 하나 있으면
    if(c) ret.insert(ret.begin() + ret.size()/2, c);
    if(flag==2) cout << "I'm Sorry Hansoo";
    else cout << ret << "\n";
    return 0;
}