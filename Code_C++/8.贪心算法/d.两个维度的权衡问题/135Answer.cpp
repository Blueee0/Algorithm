class Solution {
    public:
        int candy(vector<int>& ratings) {
            vector<int> CandyVec(ratings.size(), 1); // 默认每个孩子一个糖果
    
            // 从前往后：右孩子大于左孩子
            for (int i = 1; i < ratings.size(); i++) {
                if (ratings[i] > ratings[i - 1])
                    CandyVec[i] = CandyVec[i - 1] + 1;
            }
    
            // 从后往前：左孩子大于右孩子
            for (int i = ratings.size() - 2; i >= 0; i--) {
                if (ratings[i] > ratings[i + 1])
                    CandyVec[i] = max(CandyVec[i], CandyVec[i + 1] + 1);
            }
    
            // 统计结果
            int result = 0;
            for (int i = 0; i < ratings.size(); i++) {
                result += CandyVec[i];
            }
            return result;
        }
    };