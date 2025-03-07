class Solution {
    public:
        static bool cmp(const vector<int>& a, const vector<int>& b) {
            return a[0] < b[0]; // 左边界排序
        }
        vector<vector<int>> merge(vector<vector<int>>& intervals) {
            vector <vector<int>> result;
            if (intervals.size() == 0)
                return result;
    
            // 按左边界排序
            sort(intervals.begin(), intervals.end(), cmp);
    
            // 第一个区间就可以放进结果集里，后面如果重叠，在result上直接合并
            result.push_back(intervals[0]);
    
            for (int i = 1; i < intervals.size(); i++) {
                if (intervals[i][0] > result.back()[1]) { // 区间不重叠
                    result.push_back(intervals[i]);
                } else {
                    // 区间重叠就要合并，只更新右边界就好
                    result.back()[1] = max(result.back()[1], intervals[i][1]);
                }
            }
            return result;
        }
    };