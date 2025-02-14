class Solution {
    public:
        string removeDuplicates(string s) {
            stack<char> st;
            string ans = "";
    
            // 匹配并消除
            for (int i = 0; i < s.size(); i++) {
                if (st.empty() || s[i] != st.top()) {
                    st.push(s[i]);
                } else { // s 与 st.top()相等的情况
                    st.pop();
                }
            }
    
            // 输出栈中元素
            while (!st.empty()) { // 将栈中元素放到result字符串汇总
                ans += st.top();
                st.pop();
            }
            reverse(ans.begin(), ans.end()); // 此时字符串需要反转一下
            return ans;
        }
    };