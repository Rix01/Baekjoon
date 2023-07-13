#include <bits/stdc++.h>
using namespace std;
string s;
int main() {
    getline(cin, s);        // 공백까지 포함해서 받기
    for (int i = 0; i < s.size(); i++) {
        if (s[i]>64 && s[i]<91) {
            if (s[i] + 13 > 90) {
                s[i] = s[i] + 13 - 26;
            }
            else {
                s[i] = s[i] + 13;
            }
        }
        // 소문자
        else if (s[i]>96 && s[i]<123) {
            // +13을 했는데 범위 초과
            if (s[i] + 13 > 122) {
                s[i] = s[i] + 13 - 26;
            }
            else {
                s[i] = s[i] + 13;
            }
        }
        cout << s[i] << "";
    }
}