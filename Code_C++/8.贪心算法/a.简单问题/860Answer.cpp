class Solution {
    public:
        bool lemonadeChange(vector<int>& bills) {
            int five = 0, ten = 0;
            for (int bill : bills) {
                // 情况一
                if (bill == 5)
                    five++;
    
                // 情况二
                if (bill == 10) {
                    if (five <= 0)
                        return false;
                    ten++;
                    five--;
                }
    
                // 情况三
                if (bill == 20) {
                    // 优先消耗10美元，因为5美元的找零用处更大，能多留着就多留着
                    if (five > 0 && ten > 0) {
                        five--;
                        ten--;
                    } else if (five >= 3) {
                        five -= 3;
                    } else
                        return false;
                }
            }
            return true;
        }
    };