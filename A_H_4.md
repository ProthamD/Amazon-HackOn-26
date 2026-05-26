# Problem 4 - Minimum Energy To Collect Bags

## Question
Bob has N bags in a row. He can take either the leftmost or rightmost bag. Taking from the left costs Wi * X and taking from the right costs Wi * Y. If he picks from the same side consecutively, an extra side-specific penalty is added. Find the minimum total energy to collect all bags.

## Intuition
- The remaining bags always form a contiguous interval, so a range DP is natural.
- The state dp(l, r, last) means the minimum cost to remove bags from l to r when the previous pick came from last.
- At every state, choose left or right and add the matching base cost.
- If the chosen side equals last, add the corresponding consecutive-pick penalty.
- Memoization prevents recomputing the same interval and previous-side combination.

## Visual Representation
~~~mermaid
flowchart TD
    S[dp(l, r, last)] --> E{l > r?}
    E -- yes --> Z[0 cost]
    E -- no --> L[Pick left: W[l] * X plus left penalty if needed]
    E -- no --> R[Pick right: W[r] * Y plus right penalty if needed]
    L --> L2[dp(l+1, r, L)]
    R --> R2[dp(l, r-1, R)]
    L2 --> M[Take minimum]
    R2 --> M
~~~

## Explanation
There are O(N^2 * 3) states and each state tries two transitions, so time is O(N^2) and memory is O(N^2).

The main idea is to keep the state small enough that every decision can be checked directly. The code follows the transitions described above and prints the best value found for the problem.

## Code
~~~~cpp
// Problem 4: Bob has N bags in a row. Each bag has a weight (Wi). Bob can collect bags from either the leftmost or rightmost position, but there are energy costs: - The cost of collecting a bag is the bag's weight (Wi) multiplied by X (if collecting from the left) or Y (if collecting from the right). - If you are collecting a bag consecutively from the same side twice in a row, then there's an additional cost of El (it collected from the left side consecutively) or Er (if collected from the right side consecutively).

// Find the strategy that minimizes the total energy cost Bob spends to collect all the bags and display the minimum cost Bob has to pay.

// Input Format The first line of input contains five space-separated integers: N (number of bags), X, Y, El, Er (energy costs) The second line of input contains N space-separated integers representing the weight of each beg (Wi). output Format: Display the minimum energy cost expenditure for Bob

// Sample Testcase : Input:

// 3 4 4 19 1

// 42 3 99

// Output: 576 (collect from left then right and then left) Observation: Maybe range dp helps here? is a non dp way possible?



// intuition: 
// ## State: `dp(l, r, last)`

// - `l` = leftmost remaining bag index
// - `r` = rightmost remaining bag index
// - `last` = which side you picked from previously

// We need two indexes because as we pick bags, **the remaining bags always stay contiguous** — left pointer moves right, right pointer moves left.

// ---

// ## Dry Run

// Bags: `[42, 3, 99]` → index 0, 1, 2

// ```
// dp(0, 2, none)
// ├── pick left (42):  42*4 = 168,  dp(1, 2, L)
// │     ├── pick left (3):   3*4 + 19 = 31,  dp(2, 2, L)
// │     │     └── pick left (99): 99*4 + 19 = 415
// │     │         = 446 ❌
// │     └── pick right (99): 99*4 = 396,  dp(1, 1, R)
// │           └── pick left (3): 3*4 = 12
// │               = 408 ✓
// │   = 168 + 408 = 576
// │
// └── pick right (99): 99*4 = 396,  dp(0, 1, R)
//       ├── pick left (42):  42*4 = 168,  dp(1, 1, L)
//       │     └── pick left (3): 3*4 + 19 = 31
//       │         = 199
//       └── pick right (3):  3*4 + 1 = 13,  dp(0, 0, R)
//             └── pick left (42): 42*4 = 168
//                 = 181
//       = 396 + 181 = 577

// Answer = min(576, 577) = 576 ✅
```


#include <bits/stdc++.h>
using namespace std;

int N, X, Y, El, Er;
vector<int> W;
int memo[1001][1001][3];


int dp(int l, int r, int last) {
    if (l > r) return 0;
    
    if (memo[l][r][last] != -1) return memo[l][r][last];
    

    int penalty_left = (last == 0) ? El : 0;
    int cost_left = W[l] * X + penalty_left + dp(l + 1, r, 0);
    
    int penalty_right = (last == 1) ? Er : 0;
    int cost_right = W[r] * Y + penalty_right + dp(l, r - 1, 1);
    
    return memo[l][r][last] = min(cost_left, cost_right);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    cin >> N >> X >> Y >> El >> Er;
    W.resize(N);
    for (int i = 0; i < N; i++) cin >> W[i];
    
    memset(memo, -1, sizeof(memo));
    
    cout << dp(0, N - 1, 2) << endl;
    
    return 0;
}
~~~~
