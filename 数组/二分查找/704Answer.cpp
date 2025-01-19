class Solution {
public:
    // ��������ҿ������� [left,right)
    int search(vector<int>& nums, int target) {
    int left = 0;
    int right = nums.size(); // ��Ϊright�±겻����[left,right)
    while(left < right){    // ��Ϊleft == right��ʱ����[left, right)����Ч�Ŀռ䣬����ʹ�� <
        int middle = left + ((right - left) / 2);// ��ֹ��� ��ͬ��(left + right)/2
        if (nums[middle] > target){ //target��������
            right = middle;
        }else if(nums[middle]<target){//target��������
            left = middle+1;    // target ��[middle + 1, right)��
        }else{
            return middle;
        }
    }
    // δ�ҵ�Ŀ��ֵ
    return -1;
    }
};
