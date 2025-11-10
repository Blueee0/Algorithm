class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        int leftBorder = getLeftBorder(nums, target);
        int rightBorder = getRightBorder(nums, target);
        // ���һ��target �����鷶Χ���ұ߻�����ߣ���������{3, 4, 5}��targetΪ2��������{3, 4, 5},targetΪ6����ʱӦ�÷���{-1, -1}
        if (leftBorder == -2 || rightBorder == -2) {
            return {-1, -1};}
        // �������target �����鷶Χ�У��������д���target����������{3,6,7},targetΪ6����ʱӦ�÷���{1, 1}
        if (rightBorder - leftBorder >= 1) {
            return {leftBorder, rightBorder-1};}
        // �������target �����鷶Χ�У��������в�����target����������{3,6,7},targetΪ5����ʱӦ�÷���{-1, -1}
        return {-1, -1};
    }
private:
    int getLeftBorder(vector<int>& nums, int target){
        // ����ҿ� [left,right)
        int left = 0;
        int right = nums.size();
        int leftBorder = -2; // ��¼һ��leftBorderû�б���ֵ�����
        while (left < right){
            int middle = left + ((right - left) / 2);
            if(nums[middle] >= target){ // target �����, Ѱ����߽磬nums[middle] == target��ʱ�����right
                right = middle;
                leftBorder = right; 
            }else{
                left = middle + 1;
            }
        }
        return leftBorder;
    }
    int getRightBorder(vector<int>& nums, int target){
        // ����ҿ� [left,right)
        int left = 0;
        int right = nums.size();
        int rightBorder = -2; // ��¼һ��rightBorderû�б���ֵ�����
        while (left < right){
            int middle = left + ((right - left) / 2);
            if(nums[middle] > target){ // target �����
                right = middle;
            }else{ // Ѱ���ұ߽磬nums[middle] == target��ʱ�����left
                left = middle + 1;
                rightBorder = left;
            }
        }
        return rightBorder;
    }
};