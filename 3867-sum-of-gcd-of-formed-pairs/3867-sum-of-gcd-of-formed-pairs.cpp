class Solution {
public:
    long long gcdSum(vector<int>& nums) {
        int n=nums.size();
        vector<int>pgcd(n);
        int mx=0;
        for(int i=0;i<n;i++){
            mx=max(mx,nums[i]);
            pgcd[i]=gcd(nums[i],mx);
        }
        sort(pgcd.begin(),pgcd.end());
        long long tsum=0;
        for(int i=0;i<n/2;i++){
            tsum+=gcd(pgcd[i],pgcd[n-i-1]);
        }
        return tsum;
    }
};