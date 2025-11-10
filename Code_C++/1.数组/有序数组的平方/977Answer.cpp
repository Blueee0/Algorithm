class Solution {
public:
    vector<int> sortedSquares(vector<int>& nums) {
        int n = nums.size();
        vector<int> result(n);  // 创建一个新的数组来存储结果
        int k = n-1;
        for(int i=0,j=n-1; i<=j ;){
            int a = nums[i]*nums[i];
            int b = nums[j]*nums[j];
            if(a >= b){
                result[k]=a;
                i++;
                k--;
            }else{
                result[k]=b;
                j--;
                k--;
            }
        }
        return result;
    }
};