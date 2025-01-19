class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        int leftBorder = getLeftBorder(nums, target);
        int rightBorder = getRightBorder(nums, target);
        // 情况一：target 在数组范围的右边或者左边，例如数组{3, 4, 5}，target为2或者数组{3, 4, 5},target为6，此时应该返回{-1, -1}
        if (leftBorder == -2 || rightBorder == -2) {
            return {-1, -1};}
        // 情况三：target 在数组范围中，且数组中存在target，例如数组{3,6,7},target为6，此时应该返回{1, 1}
        if (rightBorder - leftBorder >= 1) {
            return {leftBorder, rightBorder-1};}
        // 情况二：target 在数组范围中，且数组中不存在target，例如数组{3,6,7},target为5，此时应该返回{-1, -1}
        return {-1, -1};
    }
private:
    int getLeftBorder(vector<int>& nums, int target){
        // 左闭右开 [left,right)
        int left = 0;
        int right = nums.size();
        int leftBorder = -2; // 记录一下leftBorder没有被赋值的情况
        while (left < right){
            int middle = left + ((right - left) / 2);
            if(nums[middle] >= target){ // target 在左边, 寻找左边界，nums[middle] == target的时候更新right
                right = middle;
                leftBorder = right; 
            }else{
                left = middle + 1;
            }
        }
        return leftBorder;
    }
    int getRightBorder(vector<int>& nums, int target){
        // 左闭右开 [left,right)
        int left = 0;
        int right = nums.size();
        int rightBorder = -2; // 记录一下rightBorder没有被赋值的情况
        while (left < right){
            int middle = left + ((right - left) / 2);
            if(nums[middle] > target){ // target 在左边
                right = middle;
            }else{ // 寻找右边界，nums[middle] == target的时候更新left
                left = middle + 1;
                rightBorder = left;
            }
        }
        return rightBorder;
    }
};