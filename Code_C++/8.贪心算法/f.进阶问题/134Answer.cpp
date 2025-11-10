class Solution {
    public:
        int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
            int curSum = 0;   // 当前的剩余和
            int totalSum = 0; // 所有的剩余和
            int start = 0;
            for (int i = 0; i < gas.size(); i++) {
                curSum += gas[i] - cost[i];
                totalSum += gas[i] - cost[i];
                // 当前累加剩余油量之和curSum一旦小于0，说明从i+1开始找
                if (curSum < 0) {
                    start = i + 1;
                    curSum = 0;
                }
            }
            // 所有油量都不足以跑完一圈，则-1；否则在i+1的位置一定可以跑完
            if (totalSum < 0)
                return -1;
            return start;
        }
    };