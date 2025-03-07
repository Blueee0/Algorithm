class Solution {
    public:
        int monotoneIncreasingDigits(int n) {
            string str = to_string(n);
    
            // flag用来标记赋值9从哪里开始
            // 设置为这个默认值，为了防止第二个for循环在flag没有被赋值的情况下执行
            int flag = str.size();
    
            for (int i = str.size() - 1; i > 0; i--) {
                if (str[i - 1] > str[i]) {
                    str[i - 1]--;
                    flag = i;
                }
            }
    
            for (int i = flag; i < str.size(); i++) {
                str[i] = '9';
            }
    
            return stoi(str);
        }
    };