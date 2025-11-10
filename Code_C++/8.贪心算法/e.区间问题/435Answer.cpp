class Solution {
    public:
        static bool cmp(const vector<int>& a, const vector<int>& b) {
            return a[0] < b[0]; // 左边界排序
        }
        int eraseOverlapIntervals(vector<vector<int>>& intervals) {
            if (intervals.size() == 0)
                return 0;
            sort(intervals.begin(), intervals.end(), cmp);
    
            int cnt = 1; // 区间不为空，至少有一个非重叠区间
    
            for (int i = 1; i < intervals.size(); i++) {
                // i的左边界 >= i-1的右边界，区间不重叠
                if (intervals[i][0] >= intervals[i - 1][1]) {
                    cnt++;
                } else { // 更新重叠区间的最小右边界
                    intervals[i][1] = min(intervals[i - 1][1], intervals[i][1]);
                }
            }
            return intervals.size() - cnt;
        }
    };