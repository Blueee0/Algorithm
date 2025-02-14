class Solution {
    private:
        class MyQueue { // ʵ�ֵ�������
        public:
            deque<int> que;
    
            // ÿ�ε�����ʱ�򣬱Ƚϵ�ǰҪ��������ֵ�Ƿ���ڶ��г���Ԫ�ص���ֵ���������򵯳�
            void pop(int val) {
                if (!que.empty() && val == que.front()) {
                    que.pop_front();
                }
            }
    
            // ���push����ֵ�������Ԫ�ص���ֵ����ô�ͽ����к�˵���ֵ����
            void push(int val) {
                while (!que.empty() && val > que.back()) {
                    que.pop_back();
                }
                que.push_back(val);
            }
    
            // ��ѯ��ǰ����������ֵ ֱ�ӷ��ض���ǰ��Ҳ����front�Ϳ����ˡ�
            int getMaxValue() { return que.front(); }
        };
    
    public:
        vector<int> maxSlidingWindow(vector<int>& nums, int k) {
            MyQueue que;
            vector<int> result;
    
            // �Ƚ�ǰk��Ԫ�طŽ�����
            for (int i = 0; i < k; i++) {
                que.push(nums[i]);
            }
    
            // result ��¼ǰk��Ԫ�ص����ֵ
            result.push_back(que.getMaxValue());
    
            for (int i = k; i < nums.size(); i++) {
                que.pop(nums[i - k]);          // ���������Ƴ���ǰ��Ԫ��
                que.push(nums[i]);             // ��������ǰ����������Ԫ��
                result.push_back(que.getMaxValue()); // ��¼��Ӧ�����ֵ
            }
            return result;
        }
    };