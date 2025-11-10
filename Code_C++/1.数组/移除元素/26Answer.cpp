class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        int slowIndex = 1; // ×¢ÒâslowºÍfast¶ÔÆë
        for(int fastIndex = 1; fastIndex < nums.size() ; fastIndex++){
            if(nums[fastIndex-1] != nums[fastIndex]){
                nums[slowIndex] = nums[fastIndex];
                slowIndex++;
            }
        }
        return slowIndex;
    }
};