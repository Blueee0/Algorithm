class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        unordered_map<string, vector<string>> m;
        for (string& s : strs) {
            string sorted_s = s;
            ranges::sort(sorted_s);
            m[sorted_s].push_back(s); // sorted_s 相同的字符串分到同一组
        }

        vector<vector<string>> ans;
        ans.reserve(m.size()); // 预分配空间
        for (auto& [_, value] : m) {
            ans.push_back(value);
        }
        return ans;
    }
};