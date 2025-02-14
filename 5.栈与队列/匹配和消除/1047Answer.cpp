class Solution {
    public:
        string removeDuplicates(string s) {
            stack<char> st;
            string ans = "";
    
            // ƥ�䲢����
            for (int i = 0; i < s.size(); i++) {
                if (st.empty() || s[i] != st.top()) {
                    st.push(s[i]);
                } else { // s �� st.top()��ȵ����
                    st.pop();
                }
            }
    
            // ���ջ��Ԫ��
            while (!st.empty()) { // ��ջ��Ԫ�طŵ�result�ַ�������
                ans += st.top();
                st.pop();
            }
            reverse(ans.begin(), ans.end()); // ��ʱ�ַ�����Ҫ��תһ��
            return ans;
        }
    };