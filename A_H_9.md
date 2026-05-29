# Question:
### **Problem Statement**

Given an array `nums` containing $N$ distinct integers, and an integer $K$. You can perform the following operation any number of times:

* Select any contiguous sub-array of length $K$ in `nums`.
* Find the maximum number present in that current sub-array.
* Replace all elements in that sub-array with this maximum number.

Find the **minimum number of operations** required such that the first element and the last element of the array become equal (i.e., `nums[0] == nums[N-1]`).

---

### **Input Format**

1. The first line contains an integer $N$, denoting the number of elements in the array.
2. The second line contains $N$ space-separated integers, representing the elements of the array `nums`.
3. The third line contains an integer $K$, denoting the size of the operation window.

### **Output Format**

* Print a single integer representing the minimum number of operations required.

### **Constraints**

* $2 \le N, K \le 10^5$
* $1 \le nums[i] \le 10^9$
* All integers in the initial array are distinct.

---

## **Sample Test Cases**

### **Test Case 1 (Standard Case)**

* **Input:**
```text
5
1 5 2 3 4
3

```


* **Output:**
```text
2

```


* **Explanation:** The global maximum is `5`.
* *Operation 1:* Pick the sub-array from index 0 to 2: `[1, 5, 2]`. Max is 5. Array becomes `[5, 5, 5, 3, 4]`.
* *Operation 2:* Pick the sub-array from index 2 to 4: `[5, 3, 4]`. Max is 5. Array becomes `[5, 5, 5, 5, 5]`.
Now `nums[0] == nums[4]`. Total operations = 2.



### **Test Case 2 (Window Straddling)**

* **Input:**
```text
4
1 9 2 3
4

```


* **Output:**
```text
1

```


* **Explanation:** Since $K = 4$, we can select the entire array `[1, 9, 2, 3]` in a single operation. The max is `9`, so the entire array becomes `[9, 9, 9, 9]`. Total operations = 1.

### **Test Case 3 (Large Perfect Division)**

* **Input:**
```text
7
1 2 3 10 4 5 6
4

```


* **Output:**
```text
2

```


* **Explanation:** We need to cover $N - 1 = 6$ positions. Each step gives us $K - 1 = 3$ new positions. $6 / 3 = 2$ operations exactly.

### **Test Case 4 (Ceiling Round-Up Case)**

* **Input:**
```text
6
10 1 2 3 4 5
3

```


* **Output:**
```text
3

```


* **Explanation:** We need to cover $N - 1 = 5$ positions. Each step gives us $K - 1 = 2$ positions. $\lceil 5 / 2 \rceil = 3$ operations.

<img width="4096" height="3146" alt="43569" src="https://github.com/user-attachments/assets/c9908240-1d4b-48e7-b861-bb45b9c203f7" />

# Intuition:
 Basically We need to Populate it with Maximum characters from start to end.

 Doing that only have a approach of spreading window in anyside to cover up K-1 size

 ### Why K-1, when K is given?
### ans. The Question particularly mentioned that you can only replace if maximum element is in your window , so we are assuming we are filling up till K as Kth element needs to be included in next iterations window

## Basically We are finding Segements If you have grasped what the intuition or question is saying

## Formula = ceil(n-1/k-1)

```
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
```
