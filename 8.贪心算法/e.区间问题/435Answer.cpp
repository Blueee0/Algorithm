class Solution {
    public:
        static bool cmp(const vector<int>& a, const vector<int>& b) {
            return a[0] < b[0]; // ��߽�����
        }
        int eraseOverlapIntervals(vector<vector<int>>& intervals) {
            if (intervals.size() == 0)
                return 0;
            sort(intervals.begin(), intervals.end(), cmp);
    
            int cnt = 1; // ���䲻Ϊ�գ�������һ�����ص�����
    
            for (int i = 1; i < intervals.size(); i++) {
                // i����߽� >= i-1���ұ߽磬���䲻�ص�
                if (intervals[i][0] >= intervals[i - 1][1]) {
                    cnt++;
                } else { // �����ص��������С�ұ߽�
                    intervals[i][1] = min(intervals[i - 1][1], intervals[i][1]);
                }
            }
            return intervals.size() - cnt;
        }
    };