class Solution {
    int MOD = 1e9 + 7;
    typedef vector<vector<long long>> Matrix;
    
    // Helper function to multiply two square matrices
    Matrix multiply(Matrix& A, Matrix& B) {
        int sz = A.size();
        Matrix C(sz, vector<long long>(sz, 0));
        for (int i = 0; i < sz; i++) {
            for (int k = 0; k < sz; k++) {
                if (A[i][k] == 0) continue;
                for (int j = 0; j < sz; j++) {
                    C[i][j] = (C[i][j] + A[i][k] * B[k][j]) % MOD;
                }
            }
        }
        return C;
    }
    
    // Helper function for binary matrix exponentiation
    Matrix power(Matrix A, long long p) {
        int sz = A.size();
        Matrix res(sz, vector<long long>(sz, 0));
        for (int i = 0; i < sz; i++) res[i][i] = 1;
        
        while (p > 0) {
            if (p % 2 == 1) res = multiply(res, A);
            A = multiply(A, A);
            p /= 2;
        }
        return res;
    }

public:
    int zigZagArrays(int n, int l, int r) {
        int m = r - l + 1;
        
        // Base cases for small n
        if (n == 1) return m;
        if (n == 2) return (1LL * m * (m - 1)) % MOD;
        
        int states = 2 * m;
        Matrix T(states, vector<long long>(states, 0));
        
        // Build the transition matrix
        for (int v = 0; v < m; v++) {
            // From UP state v, next must be DOWN state (u + m) where u < v
            for (int u = 0; u < v; u++) {
                T[v][u + m] = 1;
            }
            // From DOWN state (v + m), next must be UP state u where u > v
            for (int u = v + 1; u < m; u++) {
                T[v + m][u] = 1;
            }
        }
        
        // Exponentiate matrix to find paths of length n - 2
        Matrix T_pow = power(T, n - 2);
        
        // Build the initial vector V0 representing length 2 counts
        vector<long long> V0(states, 0);
        for (int v = 0; v < m; v++) {
            V0[v] = v;                  // Count of valid x1 < v
            V0[v + m] = m - 1 - v;      // Count of valid x1 > v
        }
        
        // Calculate the final answer: V_final = V0 * T^(n-2)
        long long ans = 0;
        for (int i = 0; i < states; i++) {
            long long count = 0;
            for (int j = 0; j < states; j++) {
                count = (count + V0[j] * T_pow[j][i]) % MOD;
            }
            ans = (ans + count) % MOD;
        }
        
        return ans;
    }
};