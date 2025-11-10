class Solution {
    private:
        class MyQueue { // 实现单调队列
        public:
            deque<int> que;
    
            // 每次弹出的时候，比较当前要弹出的数值是否等于队列出口元素的数值，如果相等则弹出
            void pop(int val) {
                if (!que.empty() && val == que.front()) {
                    que.pop_front();
                }
            }
    
            // 如果push的数值大于入口元素的数值，那么就将队列后端的数值弹出
            void push(int val) {
                while (!que.empty() && val > que.back()) {
                    que.pop_back();
                }
                que.push_back(val);
            }
    
            // 查询当前队列里的最大值 直接返回队列前端也就是front就可以了。
            int getMaxValue() { return que.front(); }
        };
    
    public:
        vector<int> maxSlidingWindow(vector<int>& nums, int k) {
            MyQueue que;
            vector<int> result;
    
            // 先将前k的元素放进队列
            for (int i = 0; i < k; i++) {
                que.push(nums[i]);
            }
    
            // result 记录前k的元素的最大值
            result.push_back(que.getMaxValue());
    
            for (int i = k; i < nums.size(); i++) {
                que.pop(nums[i - k]);          // 滑动窗口移除最前面元素
                que.push(nums[i]);             // 滑动窗口前加入最后面的元素
                result.push_back(que.getMaxValue()); // 记录对应的最大值
            }
            return result;
        }
    };