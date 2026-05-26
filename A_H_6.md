# Problem 6 - Longest Repeated Substring With Question Marks

## Question
Given a lowercase string containing letters and question marks, replace each ? with any lowercase letter to maximize the length of an even-length substring whose first half equals its second half.

## Intuition
- Try the largest possible half length first, because the first valid match gives the answer.
- For a fixed half length L, compare s[i] with s[i + L].
- Two positions are compatible if they already match or either side is a question mark.
- A repeated substring of length 2L exists when there are L consecutive compatible comparisons.
- If no L works, reduce L and repeat.

## Visual Representation
~~~mermaid
flowchart LR
    A[Choose half length L from n/2 down to 1] --> B[Compare s[i] and s[i+L]]
    B --> C{Characters compatible?}
    C -- yes --> D[Increase consecutive count]
    C -- no --> E[Reset count]
    D --> F{count == L?}
    F -- yes --> G[Return 2L]
    F -- no --> B
    E --> B
~~~

## Explanation
The code checks every half length and scans the string for each, so the time complexity is O(n^2) and memory is O(1).

The main idea is to keep the state small enough that every decision can be checked directly. The code follows the transitions described above and prints the best value found for the problem.

## Code
~~~~cpp
// Problem 6: You are given a string S, consisting of lowercase Latin letters and/or question marks (?), your goal is to replace each question mark with any lowercase lath letter (from ' a ' to ' z ') in such a way that the length of the longest repeated substring is maximized. - A repeated substring is a segment/substring of even length within the string where the first half is identical to the second hall. - A substring is any contiguous portion of the string.

// Objective: Replace each question mark in the string S with lowercase Latin letters to create the longest possible repeated substring. Input Format The only line of input contains a string S, consisting only of lowercase Latin letters and/or question marks. output Format print a single integer, the maximum length of the longest repeated substring ad you replace each question mark in the string with some lowercase Latin letter. sample Testcase Input:

// a??a Output: 4

//Intution:
// 1. see that this kind of sliding window type problem where we need to check start and end possition of a window , eg, [a b a b] , for l = N/2 where l denotes half sized window then match index-0(a) with index-2(i+l= 2, which is a) matches right?, now go to traverse to next index and do the same, whenever it mat5ches increase consecutive count, if consecutive count becomes equal to l then we have found a repeated substring of length 2*l, so return 2*l as answer, if not then decrease l and repeat the process until l becomes 0. If l becomes 0 then return 0 as answer.

// 2* l why ? cause see l is just half size window, we are matching windows element with windows outside wlements thats why when we get valid consecutive count equal to l then we have found a repeated substring of length 2*l, so return 2*l as answer.



#include<bits/stdc++.h>
using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    string s;
    cin >> s;
    int n = s.size();
    
    for(int L = n/2; L > 0; L--){
        int consecutive = 0;
        for(int i = 0; i < n - L; i++){
            if(s[i] == s[i+L] || s[i] == '?' || s[i+L] == '?'){
                consecutive++;
                if(consecutive == L){
                    cout << 2*L << "\n";
                    return 0;
                }
            } else {
                consecutive = 0;
            }
        }
    }
    
    cout << 0 << "\n";
    return 0;
}
~~~~
