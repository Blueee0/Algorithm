class Solution {
public:
    int minSubArrayLen(int target, vector<int>& nums) {
        int i=0,sum=0;
        int subL = 0;
        int resultL=INT32_MAX;
        for(int j = 0; j < nums.size();j++){
            sum += nums[j];
            while(sum >= target){
                subL = j-i+1;
                resultL = min(subL,resultL);
                sum = sum - nums[i];
                i++;
            }
        }
        if (resultL == INT32_MAX){
            return 0;
        }else{
            return resultL;
        }
    }
};