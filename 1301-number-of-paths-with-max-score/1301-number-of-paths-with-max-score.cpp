class Solution {
public:
    vector<int> pathsWithMaxScore(vector<string>& board) {
        int n = board.size();
        int MOD = 1e9 + 7;
        
        // DP tables
        vector<vector<long>> dp_sum(n, vector<long>(n, -1));
        vector<vector<long>> dp_paths(n, vector<long>(n, 0));
        
        // Base case: Start at bottom-right
        dp_sum[n - 1][n - 1] = 0;
        dp_paths[n - 1][n - 1] = 1;
        
        // Directions mapping to moving: Up, Left, Up-Left
        vector<pair<int, int>> dirs = {{1, 0}, {0, 1}, {1, 1}};
        
        // Traverse from bottom-right to top-left
        for (int i = n - 1; i >= 0; --i) {
            for (int j = n - 1; j >= 0; --j) {
                
                // Skip obstacles and unreachable cells
                if (board[i][j] == 'X' || dp_paths[i][j] == 0) continue;
                
                // Explore valid moves
                for (auto dir : dirs) {
                    int ni = i - dir.first;
                    int nj = j - dir.second;
                    
                    if (ni >= 0 && nj >= 0 && board[ni][nj] != 'X') {
                        // Calculate score to add (Destination 'E' gives 0)
                        int val = (board[ni][nj] == 'E') ? 0 : (board[ni][nj] - '0');
                        long new_sum = dp_sum[i][j] + val;
                        
                        // We found a strictly better path score
                        if (new_sum > dp_sum[ni][nj]) {
                            dp_sum[ni][nj] = new_sum;
                            dp_paths[ni][nj] = dp_paths[i][j];
                        } 
                        // We found another path with the exact same max score
                        else if (new_sum == dp_sum[ni][nj]) {
                            dp_paths[ni][nj] = (dp_paths[ni][nj] + dp_paths[i][j]) % MOD;
                        }
                    }
                }
            }
        }
        
        // If the top-left cell was never reached, return {0, 0}
        if (dp_paths[0][0] == 0) {
            return {0, 0};
        }
        
        return {(int)dp_sum[0][0], (int)dp_paths[0][0]};
    }
};