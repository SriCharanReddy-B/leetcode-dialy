class Solution {
public:
    vector<int> sequentialDigits(int low, int high) {
        vector<int> result;
        queue<int> q;
        
        // Push initial single digits 1-9
        for (int i = 1; i <= 9; ++i) {
            q.push(i);
        }
        
        while (!q.empty()) {
            int num = q.front();
            q.pop();
            
            if (num >= low && num <= high) {
                result.push_back(num);
            }
            
            // Extract the last digit
            int lastDigit = num % 10;
            
            // If the number hasn't exceeded the high bound and we can add a sequential digit
            if (lastDigit < 9 && num <= high) {
                q.push(num * 10 + (lastDigit + 1));
            }
        }
        
        // Queue approach requires sorting because numbers like 12 (from 1) are generated 
        // before 23 (from 2), but we also process larger numbers later.
        sort(result.begin(), result.end());
        return result;
    }
};