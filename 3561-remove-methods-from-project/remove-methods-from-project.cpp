class Solution {
public:
    vector<int> remainingMethods(int n, int k, vector<vector<int>>& invocations) {
        // Step 1: Build the directed graph
        vector<vector<int>> adj(n);
        for (const auto& inv : invocations) {
            adj[inv[0]].push_back(inv[1]);
        }

        // Step 2: Find all suspicious (infected) methods using BFS
        vector<bool> suspicious(n, false);
        queue<int> q;
        
        q.push(k);
        suspicious[k] = true;

        while (!q.empty()) {
            int curr = q.front();
            q.pop();

            for (int neighbor : adj[curr]) {
                if (!suspicious[neighbor]) {
                    suspicious[neighbor] = true;
                    q.push(neighbor);
                }
            }
        }

        // Step 3: Check for external dependencies (The Quarantine Check)
        // If a healthy method calls a suspicious one, the whole removal fails.
        for (const auto& inv : invocations) {
            int u = inv[0];
            int v = inv[1];
            
            if (!suspicious[u] && suspicious[v]) {
                // Dependency found! Return all methods 0 to n-1.
                vector<int> allMethods(n);
                iota(allMethods.begin(), allMethods.end(), 0); // Fills with 0, 1, 2... n-1
                return allMethods;
            }
        }

        // Step 4: It's safe to remove. Return only the healthy methods.
        vector<int> result;
        for (int i = 0; i < n; i++) {
            if (!suspicious[i]) {
                result.push_back(i);
            }
        }

        return result;
    }
};