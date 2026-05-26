// Problem 1: You work at a company that has 5 offices, each with a distinct salary level and a priority ranking from lowest to highest as follows: Office A (1)<OfficeB(
//  10)< Office C (100)<OfficeD(
//  1,000)< Office E($ 10,000). Your work schedule is represented by a string, where each character corresponds to an office (e.g., 'D' for Office D) you work on the ith day. Your salary is calculated based on the following rule:

// Salary Calculation Rules: - If you work in an office and no higher-priority office appears after it in the sequence, you add its salary to your total salary - If you work in an office and a higher-priority office appears later in the sequence, you subtract its salary from your total salary The company allows you to change the office you work in, on any one day to maximise your total salary. Your task is to determine the maximum possible salary after making at most one such change.

// Input Format The first and only line contains a string S representing the sequence offices you worked in.

// Output Format Print the max salary you can get after changing at most one office to another office.

// Sample Testcase 1: Testease Input ABCDEEDCBA

// Testcase Output 31000

// Replacing with E in the 4th index is the best(1 based) with score of -1-10-100+10000+10000+10000+1000+100+10+1 =31000

// Observations-1: 1)Any changes made will effect only the prefix part only before that ith pos. 2)Maybe better to store for each position i which is the index right of it where the maximum element is there from subarray starting from i+1 3)Now we will try rest 4 options available to us instead of one in the original string. for each position and take the best possible answer O(4*n^2) Is this the optimised algo or it can be made better ?

// My-Intuition: • **Ascending pair exists:** Among all `i` where `s[i] < s[i+1]`, pick the one with the largest `s[i]` and replace with 'E' — that position is already subtracting, flipping the biggest loss to +10000
// • **Monotone decreasing:** No ascending pair exists, everything already adds — try replacing every position with 'E' and pick best, since left neighbour penalty varies per position, no simple greedy works
// • **All same characters:** Falls into monotone decreasing case, replacing index 0 is best since no left neighbour penalty exists there
// • **Already contains 'E':** Same greedy applies naturally, 'E' positions skipped in try-all since replacing 'E' with 'E' changes nothing
// • **Single character:** Always replace with 'E' → 10000
// • **All 'E's:** No replacement helps → n × 10000

#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int calcSalary(const string& s, int replace_idx){
    string t = s;
    if(replace_idx != -1) t[replace_idx] = 'E';
    int n = t.size();
    int sum = 0;
    for(int i = 0; i < n-1; i++){
        if(t[i] < t[i+1]){
            switch(t[i]){
                case 'A': sum -= 1; break;
                case 'B': sum -= 10; break;
                case 'C': sum -= 100; break;
                case 'D': sum -= 1000; break;
            }
        } else {
            switch(t[i]){
                case 'A': sum += 1; break;
                case 'B': sum += 10; break;
                case 'C': sum += 100; break;
                case 'D': sum += 1000; break;
                case 'E': sum += 10000; break;
            }
        }
    }
    switch(t[n-1]){
        case 'A': sum += 1; break;
        case 'B': sum += 10; break;
        case 'C': sum += 100; break;
        case 'D': sum += 1000; break;
        case 'E': sum += 10000; break;
    }
    return sum;
}

void solveDebug(string& s) {
    int n = s.size();
    int idx = -1;
    char maxi = 'A';
    char small_val = s[0];
    int small_idx = 0;

    for(int i = 0; i < n-1; i++){
        if(s[i] < s[i+1]){
            if(s[i] >= maxi){ maxi = s[i]; idx = i; }
        }
        if(s[i] < small_val){ small_val = s[i]; small_idx = i; }
    }
    if(s[n-1] < small_val) small_idx = n-1;

    // cout << "Input: " << s << '\n';
    // cout << "idx=" << idx << " small_idx=" << small_idx << '\n';

    int best;
    if(idx != -1){
        string t = s; t[idx] = 'E';
        best = calcSalary(s, idx);
    //  
    } else {
        best = calcSalary(s, -1);
        cout << "Decreasing case, trying all:\n";
        for(int i = 0; i < n; i++){
            if(s[i] != 'E'){
                string t = s; t[i] = 'E';
                int sal = calcSalary(s, i);
                // cout << "  replace idx=" << i << " → " << t << " salary=" << sal << '\n';
                best = max(best, sal);
            }
        }
        //  cout << "Best=" << best << '\n';
    }
    cout << "Output: " << best << "\n\n";
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    vector<string> tests = {
        "ABCDEEDCBA",
        "A", "E",
        "AE", "AB",
        "BA", "EA",
        "AAAA", "EEEE",
        "DCBA",
        "EDCBA",
        "ABCBA",
        "ABDC",
        "AEDC",
        "AEBCD"
    };

    for(auto s : tests){
        solveDebug(s);
    }

    return 0;
}