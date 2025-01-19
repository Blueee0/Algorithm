class Solution {
public:
    // 采用左闭右开的区间 [left,right)
    int search(vector<int>& nums, int target) {
    int left = 0;
    int right = nums.size(); // 因为right下标不属于[left,right)
    while(left < right){    // 因为left == right的时候，在[left, right)是无效的空间，所以使用 <
        int middle = left + ((right - left) / 2);// 防止溢出 等同于(left + right)/2
        if (nums[middle] > target){ //target在左区间
            right = middle;
        }else if(nums[middle]<target){//target在右区间
            left = middle+1;    // target 在[middle + 1, right)中
        }else{
            return middle;
        }
    }
    // 未找到目标值
    return -1;
    }
};
