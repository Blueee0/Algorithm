class Solution {
    public:
        bool lemonadeChange(vector<int>& bills) {
            int five = 0, ten = 0;
            for (int bill : bills) {
                // ���һ
                if (bill == 5)
                    five++;
    
                // �����
                if (bill == 10) {
                    if (five <= 0)
                        return false;
                    ten++;
                    five--;
                }
    
                // �����
                if (bill == 20) {
                    // ��������10��Ԫ����Ϊ5��Ԫ�������ô������ܶ����žͶ�����
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