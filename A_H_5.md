# Problem 5 - Maximize Product Of Tree Component Sizes

## Question
Problem 5: You are given a mystical tree with w nodes. Each node is connected to at least one other node by on edge. Your task is to sever one or more edges in the tree to split it into subtrees. The goal is to maximize the product of the sizes of these subtrees.

The size of a subtree is defined as the number of nodes it contains. The product of subtree sizes is calculated by multiplying the sizes of all subtrees together.

Write a program that takes as input the number of nodes in the tree and the edges between them, and outputs the maximum product of subtree sizes achievable after severing edges in the tree.

Input Format The first line of input contains an integer N, representing the number of nodes in the mystical tree.

The next N-1 lines each contain two space-separated integers U and V, signifying an edge between the respective nodes.

Output Format Print a number X, representing the maximum product of subtree sizes achievable after edge deletions.

Input:

5

1 2

2 3

3 4

4 5

Output: 6 

## Intuition
# Intuition

## 1. The Intuition & DP State

To solve this, we use **Depth-First Search (DFS)** and process the tree **bottom-up**.

At every node, we decide for each child:

- **Cut the edge**
- **Keep the edge**

If we **keep** the edge, the child’s connected component merges into the parent’s component.

That means the size of the parent’s active component keeps changing dynamically, so we must track it carefully.

---

# DP State

We define:

\[
dp[u][s]
\]

Where:

- `u` = current node
- `s` = size of the connected component currently containing `u`

### Meaning

`dp[u][s]` stores:

> The maximum product of sizes of all completely separated components inside the subtree of `u`,
> while the active component containing `u` has size `s`.

The component containing `u` is still “open” because it may later connect upward to the parent.

---

# Extra Variable

## `sz[u]`

\[
sz[u]
\]

Stores:

> Total processed subtree size of node `u`

Used to limit DP loops efficiently.

---

# Transition Logic

Suppose we are processing child `v` of node `u`.

For every:

- active size `su` of `u`
- active size `sv` of `v`

We have **2 choices**.

---

# Choice 1: Cut Edge `(u,v)`

Then `v` becomes a fully separated component.

Its contribution becomes:

\[
sv \times dp[v][sv]
\]

We take the best possible cut value:

\[
max\_cut_v = \max(sv \times dp[v][sv])
\]

The active component size of `u` remains unchanged.

Transition:

\[
next\_dp[su]
=
\max(next\_dp[su],\ dp[u][su] \times max\_cut_v)
\]

---

# Choice 2: Keep Edge `(u,v)`

Now the component of `v` merges into `u`.

New active size:

\[
su + sv
\]

Transition:

\[
next\_dp[su+sv]
=
\max(
next\_dp[su+sv],
dp[u][su] \times dp[v][sv]
)
\]

---

# Pseudocode


function dfs(u, parent):

    sz[u] = 1
    dp[u][1] = 1

    for each neighbor v of u:

        if v == parent:
            continue

        dfs(v, u)

        create next_dp array of size (sz[u] + sz[v] + 1)
        initialize with 0

        max_cut_v = 0

        for sv from 1 to sz[v]:
            max_cut_v =
                max(max_cut_v, sv * dp[v][sv])

        for su from 1 to sz[u]:

            if dp[u][su] == 0:
                continue

            # OPTION 1 -> CUT EDGE

            next_dp[su] =
                max(
                    next_dp[su],
                    dp[u][su] * max_cut_v
                )

            # OPTION 2 -> KEEP EDGE

            for sv from 1 to sz[v]:

                if dp[v][sv] == 0:
                    continue

                next_dp[su + sv] =
                    max(
                        next_dp[su + sv],
                        dp[u][su] * dp[v][sv]
                    )

        dp[u] = next_dp

        sz[u] += sz[v]

## Visual Representation
~~~mermaid
flowchart TD
    A[DFS child first] --> B[For each child v]
    B --> C[Compute best result if edge u-v is cut]
    B --> D[Try keeping edge u-v for every component size]
    C --> E[Update next dp with same u component size]
    D --> F[Update next dp with merged size]
    E --> G[Finish node u states]
    F --> G
    G --> H[At root maximize s * dp[root][s]]
~~~

## Explanation
For each edge, combinations of component sizes are considered. The worst-case time is O(n^3) across all merges depending on tree shape, with O(n^2) DP memory.

The main idea is to keep the state small enough that every decision can be checked directly. The code follows the transitions described above and prints the best value found for the problem.





//intuition:
// 1. The Intuition & DP StateTo solve this, we will use Depth-First Search (DFS) to traverse the tree from the bottom up. As we process each node, we need to make decisions about its connection to its children: do we cut the edge, or do we keep it?Because keeping an edge means the child's component merges with the parent's component, the size of the parent's active component keeps changing. We must track this size to know what to multiply later.The DP Array:We define our state using a 2D array: $dp[u][s]$.u: The current node we are looking at.s: The current size of the connected component containing node u.What it stores: The maximum product of the sizes of all completely severed subtrees within u's domain. (It does not yet include the size s of u's active component, because we haven't decided where to cut u from the rest of the tree above it).The Variables:sz[u]: The total number of nodes in the subtree of u we have processed so far. We use this to limit our loops so we don't do unnecessary work.max_cut_v: If we decide to cut the edge to a child v, we look at all possible sizes sv of v's component, calculate $sv \times dp[v][sv]$, and pick the maximum.The Transitions:When we are at node u and we evaluate a child v, we look at all possible active sizes for u (su) and v (sv). We have two choices:Cut the edge (u, v): We seal off v's component. It contributes sv to our overall product. u's active size (su) remains unchanged.Keep the edge (u, v): The active component of v merges with u. The new active size for u becomes su + sv. The severed subtrees already processed in u and v are combined by multiplying their products.2. PseudocodePlaintextfunction dfs(u, parent):
//     sz[u] = 1
//     dp[u][1] = 1  // Base state: node u is a component of size 1, product of severed pieces is 1

//     for each neighbor v of u:
//         if v == parent: continue
//         dfs(v, u)  // Process child completely first

//         create next_dp array of size (sz[u] + sz[v] + 1) initialized to 0

//         // Calculate the best we can do if we CUT the edge between u and v
//         max_cut_v = 0
//         for sv from 1 to sz[v]:
//             max_cut_v = maximum(max_cut_v, sv * dp[v][sv])

//         // Try merging u's current state with v's state
//         for su from 1 to sz[u]:
//             if dp[u][su] == 0: continue

//             // Option 1: CUT the edge (u, v)
//             next_dp[su] = maximum(next_dp[su], dp[u][su] * max_cut_v)

//             // Option 2: KEEP the edge (u, v)
//             for sv from 1 to sz[v]:
//                 if dp[v][sv] == 0: continue
//                 next_dp[su + sv] = maximum(next_dp[su + sv], dp[u][su] * dp[v][sv])

//         dp[u] = next_dp   // Update u's states with the results of merging child v
//         sz[u] = sz[u] + sz[v] // Update the processed size
// 3. Dry RunLet's trace your exact input: a straight line 1 - 2 - 3 - 4 - 5.We will process from the bottom up. Assume node 1 is the root.Node 5 (Leaf): * sz[5] = 1, dp[5][1] = 1.Node 4 (Merges child 5): * Before merging: dp[4][1] = 1.max_cut_5 = (size 1) * dp[5][1] = 1 * 1 = 1.If we cut: next_dp[1] = dp[4][1] * max_cut_5 = 1.If we keep: next_dp[1+1] = dp[4][1] * dp[5][1] = 1.Result: dp[4] = {1: 1, 2: 1}, sz[4] = 2.Node 3 (Merges child 4):Before merging: dp[3][1] = 1.max_cut_4 = max( 1dp[4][1], 2dp[4][2] ) = max(1, 2) = 2.If we cut: next_dp[1] = dp[3][1] * 2 = 2.If we keep: * su=1 + sv=1 -> next_dp[2] = 1 * 1 = 1.su=1 + sv=2 -> next_dp[3] = 1 * 1 = 1.Result: dp[3] = {1: 2, 2: 1, 3: 1}, sz[3] = 3.Node 2 (Merges child 3):Before merging: dp[2][1] = 1.max_cut_3 = max( 12, 21, 3*1 ) = max(2, 2, 3) = 3.If we cut: next_dp[1] = dp[2][1] * 3 = 3.If we keep: merging sizes 1, 2, and 3 yields sizes 2, 3, and 4, all with product 1.Result: dp[2] = {1: 3, 2: 2, 3: 1, 4: 1}, sz[2] = 4.Node 1 (Merges child 2):Before merging: dp[1][1] = 1.max_cut_2 = max( 13, 22, 31, 41 ) = max(3, 4, 3, 4) = 4.If we cut: next_dp[1] = 1 * 4 = 4.If we keep: merging sizes 1, 2, 3, 4 yields sizes 2, 3, 4, 5 with values 3, 2, 1, 1.Result: dp[1] = {1: 4, 2: 3, 3: 2, 4: 1, 5: 1}.Final Answer Calculation at Root 1:We must multiply the final remaining component size s by its stored severed product.$$\max_{s} (s \times dp[1][s])$$Checking all states in dp[1]:$1 \times dp[1][1] = 1 \times 4 = 4$$2 \times dp[1][2] = 2 \times 3 = 6$$3 \times dp[1][3] = 3 \times 2 = 6$$4 \times dp[1][4] = 4 \times 1 = 4$$5 \times dp[1][5] = 5 \times 1 = 5$The maximum is 6. This perfectly maps to your observation (cutting edge 3-4 leaves sizes 3 and 2, $3 \times 2 = 6$).
```
## code:
```
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int n;
vector<vector<int>> adj;
vector<vector<long long>> dp;
vector<int> sz;

void dfs(int u, int p) {
    sz[u] = 1;
    dp[u][1] = 1; // Base case: component of size 1

    for (int v : adj[u]) {
        if (v == p) continue;
        dfs(v, u);

        // next_dp holds the states for u after merging with child v
        vector<long long> next_dp(sz[u] + sz[v] + 1, 0);

        // Find the best cut possible for the subtree v
        long long max_cut_v = 0;
        for (int sv = 1; sv <= sz[v]; ++sv) {
            max_cut_v = max(max_cut_v, 1LL * sv * dp[v][sv]);
        }

        // Try all combinations of su and sv
        for (int su = 1; su <= sz[u]; ++su) {
            if (dp[u][su] == 0) continue; // Skip invalid states

            // Option 1: Cut the edge between u and v
            next_dp[su] = max(next_dp[su], dp[u][su] * max_cut_v);

            // Option 2: Keep the edge between u and v
            for (int sv = 1; sv <= sz[v]; ++sv) {
                if (dp[v][sv] == 0) continue; // Skip invalid states
                next_dp[su + sv] = max(next_dp[su + sv], dp[u][su] * dp[v][sv]);
            }
        }
        
        // Update size of processed subtree and copy back to dp[u]
        sz[u] += sz[v];
        for (int i = 1; i <= sz[u]; ++i) {
            dp[u][i] = next_dp[i];
        }
    }
}

int main() {
    // Fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    if (!(cin >> n)) return 0;

    adj.resize(n + 1);
    dp.assign(n + 1, vector<long long>(n + 1, 0));
    sz.resize(n + 1, 0);

    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // Call DFS from an arbitrary root (1-indexed)
    dfs(1, 0);

    // Find the maximum product at the root
    long long ans = 0;
    for (int s = 1; s <= n; ++s) {
        if (dp[1][s] > 0) {
            ans = max(ans, 1LL * s * dp[1][s]);
        }
    }

    cout << ans << "\n";

    return 0;
}
~~~~
```
