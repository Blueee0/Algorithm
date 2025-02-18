class Solution {
    public:
        string multiply(string num1, string num2) {
            if (num1 == "0" || num2 == "0")
                return "0";
            int m = num1.size();
            int n = num2.size();
            vector<int> ansArr(m + n + 1);
            string ans;
    
            // 用数组记录卷积和
            for (int i = m - 1; i >= 0; i--) {
                int x = num1[i] - '0';
                for (int j = n - 1; j >= 0; j--) {
                    int y = num2[j] - '0';
                    ansArr[i + j + 1] += x * y;
                    // 处理进位
                    ansArr[i + j] += ansArr[i + j + 1] / 10; // 处理进位
                    ansArr[i + j + 1] %= 10;                 // 取模保留当前位
                }
            }
    
            // 如果ansArr的最高位为0，则舍弃最高位
            int index = 0; // 跳过前导0
            while (index < m + n && ansArr[index] == 0) {
                index++;
            }
    
            for (int i = index; i < m + n; i++) {
                ans.push_back(ansArr[i] + '0');
            }
            return ans;
        }
    };