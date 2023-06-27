#include <bits/stdc++.h>
using namespace std;

int main()
{
    string s;
    int alpha[26] = {0,};   // 소문자 a : 97 (아스키코드)
    memset(alpha, 0, 26);
    getline(cin, s);        // 문자열 입력받기
    int s_size = s.length();        // 문자열 길이
    for(int i = 0; i<s_size; i++){
        alpha[(int(s[i]))-97] += 1;
    }
    for(int i = 0; i<26; i++) cout << alpha[i] << " ";

    return 0;
}
