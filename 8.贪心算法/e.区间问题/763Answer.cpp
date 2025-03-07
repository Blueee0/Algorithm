class Solution {
    public:
        vector<int> partitionLabels(string s) {
            int hash[26] = {0};
    
            // ͳ��ÿһ���ַ������ֵ�λ��
            for (int i = 0; i < s.size(); i++) {
                hash[s[i] - 'a'] = i;
            }
    
            // �����ַ�������ַ���Զ����λ���±�͵�ǰ�±���ȣ��򵽴�ָ��
            vector<int> result;
            int right = 0; // ��¼��Զ�߽�
            int left = 0;  // ��¼��ǰ�±�
    
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