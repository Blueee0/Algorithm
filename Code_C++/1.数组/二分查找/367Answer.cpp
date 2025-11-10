class Solution {
public:
    bool isPerfectSquare(int num) {
        int left = 0;
        long long right = (long long)num + 1;
        int ans = -1;
        while(left < right){
            int middle = left + (right - left) /2 ;
            if((long long)middle * middle < num){
                left = middle + 1;
            }else if((long long)middle * middle > num){
                right = middle;
            }else{
                return true;
            }
        }
        return false;
    }
};