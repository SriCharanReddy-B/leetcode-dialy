class Solution {
public:
    int zigZagArrays(int n, int l, int r) {
        // A sequence of length 1 trivially has (r - l + 1) possibilities
        if (n == 1) {
            return r - l + 1;
        }
        
        int k = r - l;  // Normalize the range to [0, r-l]
        int MOD = 1e9 + 7;
        
        // Base case for length 1 (i = 0)
        vector<int> prevRow(k + 1, 1);
        
        for (int i = 1; i < n; ++i) {
            vector<int> currRow(k + 1, 0);
            long long prev_sum = 0;
            
            if (i % 2 != 0) {
                // i % 2 != 0 means we are going UP (A[i] > A[i-1])
                // Iterate forwards to build the prefix sum
                for (int j = 0; j <= k; ++j) {
                    currRow[j] = prev_sum;
                    prev_sum = (prev_sum + prevRow[j]) % MOD;
                }
            } else {
                // i % 2 == 0 means we are going DOWN (A[i] < A[i-1])
                // Iterate backwards to build the suffix sum
                for (int j = k; j >= 0; --j) {
                    currRow[j] = prev_sum;
                    prev_sum = (prev_sum + prevRow[j]) % MOD;
                }
            }
            
            prevRow = currRow;
        }
        
        // The sum of prevRow gives us all arrays starting with an UP move.
        long long total = 0;
        for (int val : prevRow) {
            total = (total + val) % MOD;
        }
        
        // Multiply by 2 to account for arrays starting with a DOWN move.
        return (total * 2) % MOD;
    }
};