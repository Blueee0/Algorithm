class Solution {
    public:
        int trap(vector<int>& height) {
            stack<int> st; // 栈内存放下标
            int sum = 0;
            st.push(0);
    
            for (int i = 1; i < height.size(); i++) {
                if (height[i] < height[st.top()]) {
                    st.push(i);
                } else if (height[i] == height[st.top()]) {
                    st.pop();
                    st.push(i);
                } else {
                    while (!st.empty() && height[i] > height[st.top()]) {
                        int mid = st.top();
                        st.pop();
                        if (!st.empty()) {
                            int h = min(height[st.top()], height[i]) - height[mid];
                            int w = i - st.top() - 1; // 注意减一，只求中间宽度
                            sum += h * w;
                        }
                    }
                    st.push(i);
                }
            }
            return sum;
        }
    };