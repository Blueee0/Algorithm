class Solution {
    public:
        bool isValid(string s) {
            // 如果s的长度为奇数，一定不符合要求
            if (s.size() % 2 != 0)
                return false;
    
            stack<char> st;
            for (int i = 0; i < s.size(); i++) {
                if (s[i] == '(')
                    st.push(')');
                else if (s[i] == '[')
                    st.push(']');
                else if (s[i] == '{')
                    st.push('}');
                else if (st.empty() || st.top() != s[i])
                    return false;
                else
                    st.pop();
            }
            return st.empty();
        }
    };