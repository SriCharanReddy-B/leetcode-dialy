class Solution {
public:
    int subsequencePairCount(vector<int>& nums) {
        int MOD = 1e9 + 7;
        int maxNum = *max_element(nums.begin(), nums.end());
        
        // dp[g1][g2] stores combinations for GCDs g1 and g2. 0 implies empty.
        vector<vector<int>> dp(maxNum + 1, vector<int>(maxNum + 1, 0));
        dp[0][0] = 1;
        
        for (int num : nums) {
            vector<vector<int>> next_dp(maxNum + 1, vector<int>(maxNum + 1, 0));
            
            for (int g1 = 0; g1 <= maxNum; ++g1) {
                for (int g2 = 0; g2 <= maxNum; ++g2) {
                    if (dp[g1][g2] == 0) continue;
                    
                    // 1. Skip num
                    next_dp[g1][g2] = (next_dp[g1][g2] + dp[g1][g2]) % MOD;
                    
                    // 2. Add num to seq1
                    int ng1 = (g1 == 0) ? num : std::gcd(g1, num);
                    next_dp[ng1][g2] = (next_dp[ng1][g2] + dp[g1][g2]) % MOD;
                    
                    // 3. Add num to seq2
                    int ng2 = (g2 == 0) ? num : std::gcd(g2, num);
                    next_dp[g1][ng2] = (next_dp[g1][ng2] + dp[g1][g2]) % MOD;
                }
            }
            dp = move(next_dp);
        }
        
        int ans = 0;
        // Start from 1 because sequences must be non-empty
        for (int g = 1; g <= maxNum; ++g) {
            ans = (ans + dp[g][g]) % MOD;
        }
        
        return ans;
    }
};