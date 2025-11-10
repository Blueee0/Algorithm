class Solution {
public:
    int searchInsert(vector<int>& nums, int target) {
        int left = 0;
        int right = nums.size();
        // ×ó¿ªÓÒ±Õ [left, right)
        while(left < right){
            int middle = left + ((right - left) / 2);
            if (nums[middle] < target){
                left = middle + 1;
            }else if(nums[middle] > target){
                right = middle;
            }else{
                return middle;
            }
        }
        return right;
    }
};