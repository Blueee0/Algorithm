class Solution {
    public:
        vector<string> result;
    
        void backtracking(string& s, int startIndex, int times) {
            // ��times��ʾ���е��ڼ���ѭ����������ĸ�ѭ����return
            if (times == 4) {
                // �жϵ��Ķ����ַ����Ƿ�Ϸ�������Ϸ��ͷŽ�result��
                if (isValid(s, startIndex, s.size() - 1)) {
                    result.push_back(s);
                }
                return;
            }
    
            for (int i = startIndex; i < s.size(); i++) {
                // ����ַ����Ϸ���������ݹ飻������Ҫ����ݹ�
                if (isValid(s, startIndex, i)) {
                    s.insert(s.begin() + i + 1, '.');
                    backtracking(s, i + 2, times + 1);
                    s.erase(s.begin() + i + 1);
                } else {
                    continue;
                }
            }
        }
    
        /* �жϵ�ǰ�ֶ��Ƿ�Ϸ�
            - ��λ��0Ϊ��ͷ�����ֲ��Ϸ�
            - ��λ���з��������ַ����Ϸ�
            - ��λ�������255�˲��Ϸ�
        */
        bool isValid(const string& s, int start, int end) {
            if (start > end) {
                return false;
            }
    
            // 0��ͷ�����ֲ��Ϸ�
            if (s[start] == '0' && start != end) {
                return false;
            }
    
            int num = 0;
            for (int i = start; i <= end; i++) {
                // �����������ַ����Ϸ�
                if (s[i] > '9' || s[i] < '0') {
                    return false;
                }
    
                // �������255�˲��Ϸ�
                num = num * 10 + (s[i] - '0');
                if (num > 255) {
                    return false;
                }
            }
            return true;
        }
    
        vector<string> restoreIpAddresses(string s) {
            result.clear();
            // ��֦��s�ĳ�����[4,12]
            if (s.size() < 4 || s.size() > 12)
                return result;
            backtracking(s, 0, 1);
            return result;
        }
    };