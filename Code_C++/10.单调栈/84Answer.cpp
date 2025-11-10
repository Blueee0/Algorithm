class Solution {
    public:
        int largestRectangleArea(vector<int>& heights) {
            stack<int> st;
            int result = 0;
            st.push(0);
            heights.insert(heights.begin(), 0); // 数组头部加入元素0
            heights.push_back(0);               // 数组尾部加入元素0
    
            for (int i = 1; i < heights.size(); i++) {
                if (heights[i] > heights[st.top()]) {
                    st.push(i);
                } else if (heights[i] == heights[st.top()]) {
                    st.pop();
                    st.push(i);
                } else {
                    while (!st.empty() && heights[i] < heights[st.top()]) {
                        int mid = st.top();
                        st.pop();
                        if (!st.empty()) {
                            int w = i - st.top() - 1;
                            int h = heights[mid];
                            result = max(result, w * h);
                        }
                    }
                    st.push(i);
                }
            }
    
            return result;
        }
    };