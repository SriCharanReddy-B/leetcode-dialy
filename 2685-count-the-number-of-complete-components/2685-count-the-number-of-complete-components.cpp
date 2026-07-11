class Solution {
public:
    int countCompleteComponents(int n, vector<vector<int>>& edges) {
        // Step 1: Build the adjacency list
        std::vector<std::vector<int>> graph(n);
        for (const auto& edge : edges) {
            graph[edge[0]].push_back(edge[1]);
            graph[edge[1]].push_back(edge[0]);
        }
        
        std::vector<bool> visited(n, false);
        int completeCount = 0;
        
        // Step 2: Iterate through all nodes to find distinct components
        for (int i = 0; i < n; ++i) {
            if (!visited[i]) {
                // Start a BFS to explore this component
                std::queue<int> q;
                q.push(i);
                visited[i] = true;
                
                int nodeCount = 0;
                int edgeCount = 0;
                
                while (!q.empty()) {
                    int curr = q.front();
                    q.pop();
                    
                    nodeCount++;
                    // Add the degree of the current node to the total edge count
                    edgeCount += graph[curr].size();
                    
                    for (int neighbor : graph[curr]) {
                        if (!visited[neighbor]) {
                            visited[neighbor] = true;
                            q.push(neighbor);
                        }
                    }
                }
                
                // Step 3: Check if the component is complete
                // edgeCount is twice the number of actual edges 
                // (since each edge is counted once for both of its nodes)
                if (edgeCount == nodeCount * (nodeCount - 1)) {
                    completeCount++;
                }
            }
        }
        
        return completeCount;
    }
};