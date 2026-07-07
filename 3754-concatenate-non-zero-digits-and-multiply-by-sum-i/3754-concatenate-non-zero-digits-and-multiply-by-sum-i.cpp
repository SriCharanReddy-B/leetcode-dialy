class Solution {
public:
    long long sumAndMultiply(int n) {
        string m=to_string(n);
        long long x=0;
        string y="";
        for(int i=0;i<m.length();i++){
            if(m[i]>'0'){
                x+=(m[i]-'0');
                y+=m[i];
            }
        }
        if(y.empty())return 0;
        return (long long)stoll(y)*x;

    }
};