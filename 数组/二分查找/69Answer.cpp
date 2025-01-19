class Solution {
public:
    int mySqrt(int x) {
        int left = 0;
        long long right = (long long)x+1;
        int ans = -1;
        while(left < right){
            int mid = left + ((right - left)/2);
            if((long long)mid * mid <= x){
                ans = mid;
                left = mid + 1;
            }else{
                right = mid;
            }
        }
        return ans;
    }
};