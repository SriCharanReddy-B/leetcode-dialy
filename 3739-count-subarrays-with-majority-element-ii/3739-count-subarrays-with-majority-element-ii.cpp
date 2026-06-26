class Solution {
public:
    long long countMajoritySubarrays(vector<int>& nums, int target) {
        int n = nums.size();
        
        // The prefix sum can range from -n (if no elements are target) 
        // to +n (if all elements are target). 
        // A Fenwick tree requires 1-based positive indexing.
        // We use an offset of (n + 1) so our 0 prefix sum maps to n + 1.
        int offset = n + 1;
        int max_idx = 2 * n + 1; 
        
        std::vector<int> bit(max_idx + 1, 0);

        // Standard Fenwick Tree (Binary Indexed Tree) Add function
        auto add = [&](int idx, int val) {
            for (; idx <= max_idx; idx += idx & -idx) {
                bit[idx] += val;
            }
        };

        // Standard Fenwick Tree Query function (gets sum from 1 to idx)
        auto query = [&](int idx) {
            int sum = 0;
            for (; idx > 0; idx -= idx & -idx) {
                sum += bit[idx];
            }
            return sum;
        };

        long long validSubarrays = 0;
        int currentPrefix = 0;

        // Base case: before processing any elements, our prefix sum is 0.
        // We add this to our tree at index (0 + offset).
        add(0 + offset, 1);

        for (int i = 0; i < n; ++i) {
            // Apply the transformation
            currentPrefix += (nums[i] == target) ? 1 : -1;
            
            // We want to count how many previous prefix sums are strictly LESS than currentPrefix.
            // That means we query up to (currentPrefix - 1). 
            // Don't forget to apply the offset to avoid negative indices!
            validSubarrays += query(currentPrefix - 1 + offset);
            
            // Record the current prefix sum into the tree for future queries
            add(currentPrefix + offset, 1);
        }

        return validSubarrays;
    }
};