class Solution {
    public:
        int candy(vector<int>& ratings) {
            vector<int> CandyVec(ratings.size(), 1); // Ĭ��ÿ������һ���ǹ�
    
            // ��ǰ�����Һ��Ӵ�������
            for (int i = 1; i < ratings.size(); i++) {
                if (ratings[i] > ratings[i - 1])
                    CandyVec[i] = CandyVec[i - 1] + 1;
            }
    
            // �Ӻ���ǰ�����Ӵ����Һ���
            for (int i = ratings.size() - 2; i >= 0; i--) {
                if (ratings[i] > ratings[i + 1])
                    CandyVec[i] = max(CandyVec[i], CandyVec[i + 1] + 1);
            }
    
            // ͳ�ƽ��
            int result = 0;
            for (int i = 0; i < ratings.size(); i++) {
                result += CandyVec[i];
            }
            return result;
        }
    };