class Solution {
    public:
        vector<int> partitionLabels(string s) {
            int hash[26] = {0};
    
            // 统计每一个字符最后出现的位置
            for (int i = 0; i < s.size(); i++) {
                hash[s[i] - 'a'] = i;
            }
    
            // 遍历字符，如果字符最远出现位置下标和当前下标相等，则到达分割点
            vector<int> result;
            int right = 0; // 记录最远边界
            int left = 0;  // 记录当前下标
    
            for (int i = 0; i < s.size(); i++) {
                right = max(right, hash[s[i] - 'a']);
                if (i == right) {
                    result.push_back(right - left + 1);
                    left = i + 1;
                }
            }
            return result;
        }
    };