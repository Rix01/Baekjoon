// 백준 2559
#include <bits/stdc++.h>
using namespace std;
int n, k, temp, psum[100001], ret = -1000000;
// psum은 누적합
int main(){
    cin >> n >> k;
    for(int i = 1; i<=n; i++){
        cin >> temp;        // 온도 입력
        psum[i] = psum[i-1] + temp;
    }
    for(int i = k; i<=n; i++){
        ret = max(ret, psum[i] - psum[i-k]);
    }
    cout << ret <<"";
    return 0;
}