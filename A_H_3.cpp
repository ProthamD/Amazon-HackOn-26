#include<iostream>
#include<vector>
#include<algorithm>
#include<limits.h>
using namespace std;

int func(int i, vector<int>& A, int x, int M, bool picked){
    if(i == 0) return (x % M == 0 && picked) ? 0 : INT_MAX;
    int not_take = func(i-1, A, x, M, picked);
    int take = func(i-1, A, (x + A[i]) % M, M, true);
    if(take != INT_MAX) take += 1;
    return min(not_take, take);
}



void solve(){
    //my codes here
    // a , x, m will be given , I have implement6ed the above code just for understanding
    // func(n, A, x%M, M, false)
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t--) {
        solve();
    }
    
    return 0;
}