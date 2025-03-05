class Solution {
    public:
        // cmp：身高从高到低排，若相同，则按k从小到大排
        static bool cmp(const vector<int>& a, const vector<int>& b) {
            if (a[0] == b[0])
                return a[1] < b[1];
            return a[0] > b[0];
        }
    
        vector<vector<int>> reconstructQueue(vector<vector<int>>& people) {
            sort(people.begin(), people.end(), cmp);
            vector<vector<int>> que;
            for (int i = 0; i < people.size(); i++) {
                int position = people[i][1];                    // 获取k
                que.insert(que.begin() + position, people[i]);  // 插入第k个位置
            }
            return que;
        }
    };