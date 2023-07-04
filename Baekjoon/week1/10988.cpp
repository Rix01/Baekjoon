// 백준 10988
#include <bits/stdc++.h>
using namespace std;
string word;
int main(){
    cin >> word;
    int w_len = word.length();
    int mid = w_len / 2;
    int flag = 1;  // 팰린드롬인지 구별하기 위한 플래그
    // 홀수, 짝수 따로
    // 길이가 홀수일 경우
    if(w_len % 2 == 1){
        for(int i = 0; i<mid; i++){
            if(word[i] == word[mid+(mid-i)]) continue;
            else{
                flag = 0;
                break;
            }
        }
    }
    // 짝수인 경우
    else{
        int mid_e = mid - 1;
        for(int i = 0; i<mid; i++){
            if(word[i] == word[mid+(mid_e - i)]) continue;
            else{
                flag = 0;
                break;
            }
        }
    }

    cout << flag << "";
    return 0;
}