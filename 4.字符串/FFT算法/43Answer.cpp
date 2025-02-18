class Solution {
    public:
        string multiply(string num1, string num2) {
            if (num1 == "0" || num2 == "0")
                return "0";
            int m = num1.size();
            int n = num2.size();
            vector<int> ansArr(m + n + 1);
            string ans;
    
            // �������¼�����
            for (int i = m - 1; i >= 0; i--) {
                int x = num1[i] - '0';
                for (int j = n - 1; j >= 0; j--) {
                    int y = num2[j] - '0';
                    ansArr[i + j + 1] += x * y;
                    // �����λ
                    ansArr[i + j] += ansArr[i + j + 1] / 10; // �����λ
                    ansArr[i + j + 1] %= 10;                 // ȡģ������ǰλ
                }
            }
    
            // ���ansArr�����λΪ0�����������λ
            int index = 0; // ����ǰ��0
            while (index < m + n && ansArr[index] == 0) {
                index++;
            }
    
            for (int i = index; i < m + n; i++) {
                ans.push_back(ansArr[i] + '0');
            }
            return ans;
        }
    };