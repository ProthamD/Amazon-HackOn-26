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


# Intuition

## Observation

We need to find:

> The maximum length substring that is made by repeating another substring consecutively.

Example:

```text
abab
```

Here:

```text
ab + ab
```

So answer is:

```text
4
```

because the repeated substring length is `2`
and total repeated block length becomes:

\[
2 \times 2 = 4
\]

---

# Core Idea

This is a **sliding window style comparison problem**.

We try all possible half lengths:

\[
l = \frac{n}{2}, \frac{n}{2}-1, \dots, 1
\]

Where:

- `l` = size of one half

Then we compare:

```text
s[i]
with
s[i + l]
```

for all possible positions.

---

# Why Compare `i` and `i+l` ?

Because we want to check whether:

```text
[first half]
==
[second half]
```

Example:

```text
a b a b
0 1 2 3
```

For:

\[
l = 2
\]

Compare:

```text
index 0 with index 2
a == a
```

```text
index 1 with index 3
b == b
```

Both matched.

That means:

```text
ab == ab
```

So:

```text
abab
```

is a repeated substring.

---

# Consecutive Match Count

We maintain:

```text
consecutive_count
```

Whenever:

```text
s[i] == s[i+l]
```

increase count.

Otherwise reset it to `0`.

---

# Important Observation

If:

```text
consecutive_count == l
```

then we found:

```text
[l sized substring]
repeated twice consecutively
```

which means total valid substring length becomes:

\[
2 \times l
\]

So immediately return:

\[
2l
\]

---

# Why Return `2*l` ?

Because:

- `l` only represents HALF of the repeated block
- We are matching:

```text
left window
with
right window
```

So total repeated substring size becomes:

```text
left half + right half
```

\[
l + l = 2l
\]

---

# Algorithm

## Step 1

Start from:

\[
l = \frac{n}{2}
\]

because repeated substring must contain at least 2 equal halves.

---

## Step 2

Compare:

```text
s[i]
with
s[i+l]
```

for all valid indices.

---

## Step 3

If characters match:

```text
consecutive_count++
```

Else:

```text
consecutive_count = 0
```

---

## Step 4

If:

```text
consecutive_count == l
```

return:

\[
2l
\]

---

## Step 5

If not found:

```text
l--
```

and repeat.

---

# Pseudocode

```text
for l from n/2 down to 1:

    consecutive_count = 0

    for i from 0 to n-l-1:

        if s[i] == s[i+l]:

            consecutive_count++

        else:

            consecutive_count = 0

        if consecutive_count == l:

            return 2*l

return 0
```

---

# Dry Run

String:

```text
abab
```

Length:

```text
n = 4
```

---

# Try `l = 2`

We compare:

```text
s[i]
with
s[i+2]
```

---

## i = 0

Compare:

```text
s[0] = a
s[2] = a
```

Match.

```text
consecutive_count = 1
```

---

## i = 1

Compare:

```text
s[1] = b
s[3] = b
```

Match again.

```text
consecutive_count = 2
```

Now:

```text
consecutive_count == l
```

So repeated substring found.

Return:

\[
2 \times l
=
2 \times 2
=
4
\]

---

# Final Answer

```text
4
```

because:

```text
abab = ab + ab
```

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
