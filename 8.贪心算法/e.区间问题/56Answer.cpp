class Solution {
    public:
        static bool cmp(const vector<int>& a, const vector<int>& b) {
            return a[0] < b[0]; // ��߽�����
        }
        vector<vector<int>> merge(vector<vector<int>>& intervals) {
            vector <vector<int>> result;
            if (intervals.size() == 0)
                return result;
    
            // ����߽�����
            sort(intervals.begin(), intervals.end(), cmp);
    
            // ��һ������Ϳ��ԷŽ���������������ص�����result��ֱ�Ӻϲ�
            result.push_back(intervals[0]);
    
            for (int i = 1; i < intervals.size(); i++) {
                if (intervals[i][0] > result.back()[1]) { // ���䲻�ص�
                    result.push_back(intervals[i]);
                } else {
                    // �����ص���Ҫ�ϲ���ֻ�����ұ߽�ͺ�
                    result.back()[1] = max(result.back()[1], intervals[i][1]);
                }
            }
            return result;
        }
    };