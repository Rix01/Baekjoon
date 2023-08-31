// 백준 9996
#include <bits/stdc++.h>
using namespace std;
string pat, pre, suf, ret;
int main(){
    int n;  // 파일의 개수 n
    cin >> n;
    cin >> pat; // 패턴
    int pos = pat.find('*');
    pre = pat.substr(0, pos);
    suf = pat.substr(pos+1);
    for(int i = 0; i < n; i++){
        cin >> ret;
        // 일치는 DA, 불일치는 NE
        if(pre.size() + suf.size() > ret.size()){
            cout << "NE" << "\n";
        }
        else{
            if(pre == ret.substr(0, pre.size()) && suf == ret.substr(ret.size()-suf.size())) cout <<"DA" << "\n";
            else cout << "NE" << "\n";
        }
    }
    return 0;
}