#include<iostream>
#include<vector>
#include<algorithm>
#include<limits.h>
using namespace std;

void solve(){
    //my codes here
    int n,k;
    cin >> n >> k;
    vector<int> a(n);
    for(int i = 0; i < n; i++) {
        cin >> a[i];
    }
    cout << (n-1+k-2)/(k-1) << endl; // ceiling of (n-1)/(k-1)
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