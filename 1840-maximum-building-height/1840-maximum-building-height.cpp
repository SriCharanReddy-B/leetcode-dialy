class Solution {
public:
    int maxBuilding(int n, vector<vector<int>>& restrictions) {
        // Step 1: Add the base constraint for building 1 and sort
        restrictions.push_back({1, 0});
        sort(restrictions.begin(), restrictions.end());
        
        int m = restrictions.size();
        
        // Step 2: Left-to-Right Pass
        // Ensure no building exceeds the height allowed by the building to its left
        for (int i = 1; i < m; ++i) {
            int prev_id = restrictions[i-1][0];
            int prev_h  = restrictions[i-1][1];
            int curr_id = restrictions[i][0];
            int curr_h  = restrictions[i][1];
            
            restrictions[i][1] = min(curr_h, prev_h + (curr_id - prev_id));
        }
        
        // Step 3: Right-to-Left Pass
        // Ensure no building exceeds the height allowed by the building to its right
        for (int i = m - 2; i >= 0; --i) {
            int next_id = restrictions[i+1][0];
            int next_h  = restrictions[i+1][1];
            int curr_id = restrictions[i][0];
            int curr_h  = restrictions[i][1];
            
            restrictions[i][1] = min(curr_h, next_h + (next_id - curr_id));
        }
        
        int max_height = 0;
        
        // Step 4: Find the maximum peak between any two adjacent restricted buildings
        for (int i = 1; i < m; ++i) {
            int prev_id = restrictions[i-1][0];
            int prev_h  = restrictions[i-1][1];
            int curr_id = restrictions[i][0];
            int curr_h  = restrictions[i][1];
            
            // Peak calculation
            int peak = (prev_h + curr_h + curr_id - prev_id) / 2;
            max_height = max(max_height, peak);
        }
        
        // Step 5: Check the trailing buildings (from the last restriction up to n)
        int last_id = restrictions.back()[0];
        int last_h  = restrictions.back()[1];
        
        max_height = max(max_height, last_h + (n - last_id));
        
        return max_height;
    }
};