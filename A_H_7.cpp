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