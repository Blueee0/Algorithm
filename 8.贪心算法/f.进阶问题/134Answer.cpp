class Solution {
    public:
        int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
            int curSum = 0;   // ��ǰ��ʣ���
            int totalSum = 0; // ���е�ʣ���
            int start = 0;
            for (int i = 0; i < gas.size(); i++) {
                curSum += gas[i] - cost[i];
                totalSum += gas[i] - cost[i];
                // ��ǰ�ۼ�ʣ������֮��curSumһ��С��0��˵����i+1��ʼ��
                if (curSum < 0) {
                    start = i + 1;
                    curSum = 0;
                }
            }
            // ��������������������һȦ����-1��������i+1��λ��һ����������
            if (totalSum < 0)
                return -1;
            return start;
        }
    };