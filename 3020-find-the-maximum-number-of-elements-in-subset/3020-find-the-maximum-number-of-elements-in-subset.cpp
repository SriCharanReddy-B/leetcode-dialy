class Solution {
public:
    int maximumLength(vector<int>& nums) {
        unordered_map<long long, int> count;
        int max_num = 0;
        
        // Build frequency map and find the maximum number 
        for (int num : nums) {
            count[num]++;
            max_num = max(max_num, num);
        }
        
        // Handle the special case for base 1 
        int ans = 1;
        if (count.count(1)) {
            ans = count[1] - (count[1] % 2 == 0 ? 1 : 0);
        }
        
        // Test every unique number as a potential base
        for (const auto& [num, freq] : count) {
            if (num == 1) continue;
            
            int length = 0;
            long long x = num;
            
            // Grow the sequence outward as long as we have matching pairs
            while (x <= max_num && count.count(x) && count[x] >= 2) {
                length += 2;
                x *= x;
            }
            
            // If the next square exists, it safely crowns the sequence as the peak (+1).
            // If it doesn't, we went one step too far and must use the previous 
            // paired element as our peak instead, breaking its pair (-1).
            if (count.count(x)) {
                ans = max(ans, length + 1);
            } else {
                ans = max(ans, length - 1);
            }
        }
        
        return ans;
    }
};