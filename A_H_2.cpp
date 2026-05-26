// Problem 2: A company is organizing an internship program and categorizes interns into three types based on their referral capability: - Type A interns each refer two new candidates. - Type B interns each refer one new candidate. - Type C interns do not refer any new candidates.

// Based on the above rule the interns form a binary tree like structure in which type A have two referred interns, type B have one referred intern and type C do not have any referred interns.

// The goal is to find the shortest path from the first intern who initiates referrals to the most recently referred intern, ensuring that all interns are included. If it's not possible to include all Interns within a certain numb: of referral steps, the solution should indicate that it's not feasible(-1).

// Input Format First line contains T representing the number of test cases. First line of each test case contain three numbers a,b,c representing the count of interns of each type: - a represents the number of Type A interns who refer two candidates each. - b represents the number of Type B interns who refer one candidate each. - c represents the number of Type C interns who do not refer any candidates.

// Output Format Print the length of the shortest referral chain that could be created or print -1 if it is not feasible.

// intuition:
// ## Core Intuition
// total nodes n = a + b + c
// total edges  = 2a + b
// but edges = n - 1 always in a tree
// so: 2a + b = a + b + c - 1
// →  a - c = -1
// →  c = a + 1
// Think of `slots` as **open seats** at each level:

// ```
// A → fills 1 seat, opens 2 new seats
// B → fills 1 seat, opens 1 new seat
// C → fills 1 seat, opens 0 new seats
// ```

// ---

// ## Why `+=`

// At level with `slots=3, a=1, b=1`:

// ```
// [ _ ][ _ ][ _ ]

// place A:  [ A ][ _ ][ _ ]   next_slots = 2
//             ↓↓
// place B:  [ A ][ B ][ _ ]   next_slots += 1 = 3
//                 ↓
// place C:  [ A ][ B ][ C ]   next_slots stays 3
// ```

// Next level has **3 slots = 2 from A + 1 from B**, both contributed together, so we need `+=` to accumulate both. If it was `=`:
// ```
// next_slots = use_b = 1   ← lost A's 2 slots!
// ```

// That's it — `+=` just means **A and B both contribute to next level's slots simultaneously**.


#include<iostream>
#include<vector>
using namespace std;

int solve(long long a, long long b, long long c){
    if(c != a + 1) return -1;

    int level = 0;
    long long slots = 1;

    while(slots > 0){
        long long use_a = min(slots, a);
        slots -= use_a;
        a     -= use_a;
        long long next_slots = use_a * 2;

        long long use_b = min(slots, b);
        slots -= use_b;
        b     -= use_b;
        next_slots += use_b;

        long long use_c = min(slots, c);
        slots -= use_c;
        c     -= use_c;

        if(a == 0 && b == 0 && c == 0) return level;

        level++;
        slots = next_slots;

        if(slots == 0 && (a+b+c) > 0) return -1;
    }
    return level;
}


// main function is just for runing test cases; so take it easy

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    // {a, b, c, expected}
    vector<tuple<long long,long long,long long,int>> tests = {
        {1, 0, 2,  1},   // A with 2 leaves:         A -> C,C
        {3, 0, 4,  2},   // perfect binary tree h=2
        {3, 1, 4,  3},   // one B pushes depth to 3
        {0, 0, 1,  0},   // single C node
        {0, 1, 1,  1},   // B with one C child
        {2, 0, 3,  2},   // unbalanced, not perfect power of 2
        {7, 0, 8,  3},   // perfect binary tree h=3
        {0, 3, 1,  3},   // pure B chain
        {2, 2, 3,  3},   // mix of all three
        {1, 0, 1, -1},   // c != a+1, infeasible
        {2, 0, 2, -1},   // c != a+1, infeasible
        {0, 0, 0, -1},   // empty, infeasible
    };

    int pass = 0, fail = 0;
    for(auto& [a,b,c,expected] : tests){
        int got = solve(a,b,c);
        string status = (got == expected) ? "PASS" : "FAIL";
        if(got == expected) pass++; else fail++;
        cout << status << " | a=" << a << " b=" << b << " c=" << c
             << " | expected=" << expected << " got=" << got << '\n';
    }
    cout << "\n=== " << pass << " passed, " << fail << " failed ===\n";

    int t;
    cin >> t;
    while(t--){
        long long a, b, c;
        cin >> a >> b >> c;
        cout << solve(a, b, c) << '\n';
    }
    return 0;
}