# Problem 7 - Unique Maximum Number Game

## Question
Given a multiset of numbers, repeatedly inspect the current maximum. If it is unique, count it, remove it, and insert floor(max / 2) if non-zero. If it appears multiple times, remove all copies. Output how many unique maximums were counted.

## Intuition
- A sorted frequency map lets us repeatedly access the current maximum.
- If the maximum frequency is one, it contributes to the answer and its half may affect later rounds.
- If the maximum frequency is more than one, all copies are discarded and nothing is counted.
- Processing continues until no numbers remain.

## Visual Representation
~~~mermaid
flowchart TD
    A[Build frequency map] --> B{Map empty?}
    B -- yes --> Z[Print answer]
    B -- no --> C[Take largest key]
    C --> D{frequency == 1?}
    D -- yes --> E[Increment answer]
    E --> F[Insert floor(value / 2) if non-zero]
    D -- no --> G[Discard all copies]
    F --> B
    G --> B
~~~

## intuition:
// Here is the step-by-step strategy:
// Store the frequency of every number in the array.
// Continually extract the maximum key from the frequency map.
// Check its frequency:
// If count == 1: Increment the answer tally. Calculate half = max_value / 2. If half > 0, add it to the frequency map (incrementing its count).
// If count > 1: Do nothing to the answer tally. Do not add anything back. Simply drop it.
// Delete the processed maximum key from the map entirely.
// Repeat until the map is empty.

## Explanation
Each map operation costs O(log K), where K is the number of distinct active values. The number of rounds is bounded by removals plus generated halves.

The main idea is to keep the state small enough that every decision can be checked directly. The code follows the transitions described above and prints the best value found for the problem.

## Code
~~~~cpp
// Problem 7: Bob has a collection of numbers and he loves to play a game with them. In this game, Bob counts the unique maximum numbers from his collection based on the following rules: - A number is considered unique if it is the maximum number in the collection and it does not repeat.

// -If Bob finds a unique maximum number, he counts it, removes it from the collection, and then adds half of that number back into the collection (if the half is not zero).(If its odd then just the floor part)

// -If the maximum number is not unique (it repeats) , Bob removes all occurrences of that number from the collection.

// First Line contains a single integer N representing the size of the array. The second line contains N integers representing elements of the array. Output Format Output a single integer representing the count of unique numbers that Bob will count by the end of the game.

// intuition:
// Here is the step-by-step strategy:
// Store the frequency of every number in the array.
// Continually extract the maximum key from the frequency map.
// Check its frequency:
// If count == 1: Increment the answer tally. Calculate half = max_value / 2. If half > 0, add it to the frequency map (incrementing its count).
// If count > 1: Do nothing to the answer tally. Do not add anything back. Simply drop it.
// Delete the processed maximum key from the map entirely.
// Repeat until the map is empty.

#include <iostream>
#include <map>

using namespace std;

int main() {

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    if (!(cin >> n)) return 0;
    
    // std::map automatically sorts by keys in ascending order
    map<int, int> freq;
    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;
        freq[x]++;
    }
    
    int ans = 0;
    
    // Always process the maximum element until the map is empty
    while (!freq.empty()) {
        // prev(freq.end()) points to the largest key
        auto it = prev(freq.end()); 
        int val = it->first;
        int count = it->second;
        
        // Remove the maximum element from the map entirely
        freq.erase(it);
        
        if (count == 1) {
            ans++;
            int nxt = val / 2; 
            
            if (nxt != 0) {
                freq[nxt]++;
            }
        }
        // If count > 1, we do nothing and it has already been erased
    }
    
    cout << ans << "\n";
    return 0;
}
~~~~
