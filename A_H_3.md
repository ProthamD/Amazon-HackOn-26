# Problem 3 - Minimum Picked Elements For Divisible Sum

## Question
The source file contains a recursive template for choosing a non-empty subset of array values so that the running sum modulo M becomes 0. The objective inferred from the code is to minimize how many elements are picked.

## Intuition
- The state tracks the index currently available, the current modulo value, M, and whether at least one element has been picked.
- For each item, the recursion branches into not taking it or taking it.
- Taking an item updates the modulo and adds one to the picked count.
- A base state is valid only when the modulo is 0 and at least one element was selected.
- The present file is a skeleton: solve() does not yet parse the full input or call the recursive function.

## Visual Representation
~~~mermaid
flowchart TD
    A[State func(i, mod, picked)] --> B{No items left?}
    B -- yes --> C{mod == 0 and picked?}
    C -- yes --> D[Return 0]
    C -- no --> E[Return INF]
    B -- no --> F[Option 1: skip item i]
    B -- no --> G[Option 2: take item i]
    G --> H[Update modulo and add 1]
    F --> I[Return min(skip, take)]
    H --> I
~~~

## Explanation
The raw recursive template is exponential without memoization. With memoization over index, modulo, and picked flag, it can become O(n * M).

The main idea is to keep the state small enough that every decision can be checked directly. The code follows the transitions described above and prints the best value found for the problem.

## Code
~~~~cpp
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
~~~~
